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
    int     n   =   0;   // Matrix order.
    int i,j,a;           // Loop Variables.

    double **M;
    double *Mb;

    int         my_rank;   /* My process rank           */
    int         p;         /* The number of processes   */
    int         tag = 0;
    MPI_Status  status;

    // Initialize MPI and retreive world size and p's rank.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

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
                        printf("==> Invalid arguments\n");
                        return 1;
                    }
                }
            }
        }
    }

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
    
    // Determine the order of the local matrix for each p.
    // assume for now that the p fit perfectly into n.



    print_matrix( M, n);

    // Free the matrix memory.
    free(M);
    free(Mb);

    /* Shut down MPI */
    MPI_Finalize();
}
