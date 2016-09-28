/* 
 * Brandon Bell
 * CSCI: 4576
 * HW6: Parallel Matrix Multiplication Using Fox's Algorythm
 * 9-28-16
 *
 */

// TO-DO:
//
// 1) Needed for Assignment. Make p.83 code into a matrix-matrix pruduct via n
// allgathers on on the columns and doing the dots.
//
//
// 2) Implement Fox's for square matricies. Can get matricies however.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>
#include <popt.h>

/* Paralell matrix code from p.83. */
/* void Paralled_matrix_matrix_prod( */
                                /* LOCAL_MATRIX_T     local_A, */
                                 /* int                m, */
                                 /* int                n, */
                                 /* float              local_x[], */
                                 /* float              global_x[], */
                                 /* float              local_y[], */
                                 /* int                local_m, */
                                 /* int                local_n ) */
/* { */
    /* local_m = m/p, local_n = n/p */
    /*  */
    /* int i; */
    /* int j; */
/*  */
    /* MPI_Allgather( local_x, local_n, MPI_FLOAT, global_x, local_n, MPI_FLOAT, MPI_COMM_WORLD ); */
/*  */
    /* for ( i=0; i<local_m, i++ ) */
        /* local_y[i] = local_y[i] + local_A[i][j]*global_x[j]; */
/* } */


/* // Serial Matrix Vector Product from p.78. */
/* void serial_matrix_vector_prod( */
                                /* MATRIX_T    A; */
                                /* int         m; */
                                /* int         n; */
                                /* float       x[]; */
                                /* float       y[];) */
/* { */
    /* int     k; */
    /* int     j; */
/*  */
    /* for ( k = 0; j<n; j++ ) */
    /* { */
        /* y[k] = 0.0; */
        /* for ( j = 0; j<n; j++ ) */
            /* y[k] = y[k] + A[k][j]*x[j]; */
    /* } */
/* } */


/* Paralell matrix code from p.83. */
void allgather_matrix_matrix_prod(
                                 double             **local_A,
                                 int                n,
                                 double             **local_x,
                                 double             **global_x,
                                 double             **local_y,
                                 int                local_n )
{
    int i;
    int j;

    MPI_Allgather( local_x, local_n, MPI_FLOAT, global_x, local_n, MPI_FLOAT, MPI_COMM_WORLD );

    for ( i=0; i<local_n; i++ )
        local_y[i][j] = local_y[i][j] + local_A[i][j]*global_x[j][j];
}

// Function to print the matrix
void print_matrix( double **matrix, int dim )
{
    int i;
    int j;
    for ( i=0; i<dim; i++ )
    {
    printf( "|");
        for ( j=0; j<dim; j++ )
        {   
            printf("%2.0f", (matrix[i][j] ));
        }   

        printf(" |\n");
    }
}


int main( int argc, char* argv[] )
{
    int         n       =   0;  // Matrix order.
    int         local_n =   0;  // Local Matrix order.
    int         local_m =   0;  // Local Matrix order.
    int         i,j,a;          // Loop Variables.
    double      **M;            // Global Matrix row pointers
    double      *Mb;            // Global Matrix Data
    double      **m;            // Local Matrix row pointers
    double      *mb;            // Local Matrix Data
    double      **a;            // Local Matrix row pointers
    double      *ab;            // Local Matrix Data
    int         my_rank;        // My process rank           
    int         p;              // The number of processes   
    int         tag     = 0;    // MPI Tag for
    MPI_Status  status;
    // Node name variables.
    char       name[MPI_MAX_PROCESSOR_NAME];
    int        pnamemax;

    // Initialize MPI and retreive world size and p's rank.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    // Get the node name for output.
    MPI_Get_processor_name(name,&pnamemax);

    // Parse the comand line argument for order of matricie. 
    if ( argc > 1 )
    {
        // Loop though all the arguments if more than on is present.
        for ( a=1; a<argc; a++ )
        {
            // checks for -i and a convertable int value.
            if ( !strcmp(argv[a],"-n") && (argc-1) > a && strtol( argv[a+1], NULL, 10 ) )
            {
                n = strtol( argv[2], NULL, 10 );
                if ( n == 0)
                {
                    if (my_rank == 0)
                    {
                        printf("==> [ %s, %d ], Invalid arguments\n", name, my_rank);
                        return 1;
                    }
                }
            }
        }
    }

    // Determine the order of the local matrix for each p.
    // Check that p fits perfectly into n.
    if ( p == 1 )
        local_n = n;
        local_m = n;
    else if ( n%p == 0 )
        local_n = n / p;
        local_m = n;
    else
    {
        printf("[ %s, %d ] p and n incompatible: p %d, n %d, local_n %d \n",name, my_rank, p, n, local_n);
        return 2;
    }

    // Only build the global array on p0.
    if ( my_rank == 0)
    {
        // Build the global array.
        // Build a Dynamicaly allocated contiguous 2d square matrix of size n.
        // array of row pointers.
        M = (double **) malloc( n * sizeof(double *) );
        // where data is stored.
        Mb = (double *) malloc( n * n * sizeof(double) );
        // Initialize row pointers. 
        for ( i=0; i<n; i++ )
        {
            M[i] = Mb + i * n;
        }
        // Initialize the array data to zero or 1 (identity Matrix).
        for ( i=0; i<n; i++ )
        {
            for ( j=0; j<n; j++ )
            {
                M[i][j] = 0.0;
                // Make the matrix the identiy matrix, it's just easy.
                if ( i == j )
                    M[i][j] = 1;
            }
        }
        // TO-DO: Delete this.
        print_matrix( M, n);
    }
    
    // Build the local array.
    // Build a Dynamicaly allocated contiguous 2d square matrix of size local_n.
    // array of row pointers.
    m = (double **) malloc( local_n * sizeof(double *) );
    // where data is stored.
    mb = (double *) malloc( local_n * local_m * sizeof(double) );
    // Initialize row pointers. 
    for ( i=0; i<local_n; i++ )
    {
        m[i] = mb + i * local_n;
    }
    // Initialize the array data to zero.
    for ( i=0; i<local_n; i++ )
    {
        for ( j=0; j<local_n; j++ )
        {
            m[i][j] = 0.0;
        }
    }

    /* allgather_matrix_matrix_prod( m, n,  */

    // TO-DO: delete these. 
    printf("[ %s, %d ] p %d, n %d, local_n %d \n", name, my_rank, p, n, local_n);
    print_matrix( m, local_n);

    // Free the matrix memory.
    /* free(M); */
    /* free(Mb); */
    /* free(m); */
    /* free(mb); */

    /* Shut down MPI */
    MPI_Finalize();
}
