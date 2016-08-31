/* 
 * Brandon Bell
 * csci4576
 * hw2 8-31-2016
 *
 * Part 3a: PPMPI 4.7.2-a Simpsons Rule Serial Program.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mpi.h"

// I nabbed f from the trap program.
float f(float x) {
    float return_val;
    /* Calculate f(x). */
    /* Store calculation in return_val. */
    return_val = x*x;
    return return_val;
} 

// I nabbed simpson from my serial code.
float simpson (
          float  a   /* in */,
          float  b   /* in */,
          int    n   /* in */,
          float  h   /* in */) 
{
   float integral; 
   float x = a;
   
   // Take care of the starting and end points.
   integral = f(a) + f(b);
   // Loop through the n strips in the region of integration.
   for ( int i=1; i<(2*n - 1); i++ )
   {
        // increment x by a half interval at a time (we need the mid point).
        x += h / 2;
        if ( i % 2 == 0 )
            integral += ( 2 * f(x) );
        else 
            integral += ( 4 * f(x) );
   }
   integral *= ( h / 3 );
   return integral;
}

// Most of my main is addapted from the Parallel Trap Code.
int main(int argc, char** argv) 
{
    int         my_rank;   /* My process rank           */
    int         p;         /* The number of processes   */
    float       a = 0.0;   /* Left endpoint             */
    float       b = 1.0;   /* Right endpoint            */
    int         n = 1024;  /* Number of trapezoids      */
    float       h;         /* Trapezoid base length     */
    float       local_a;   /* Left endpoint my process  */
    float       local_b;   /* Right endpoint my process */
    int         local_n;   /* Number of trapezoids for  */
                           /* my calculation            */
    float       integral;  /* Integral over my interval */
    float       total;     /* Total integral            */
    int         source;    /* Process sending integral  */
    int         dest;      /* All messages go to 0      */
    int         tag = 0;
    int         verbose = 0; // For determining verbosity level.
    MPI_Status  status;

    // Initialize MPI and retreive world size and p's rank.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // Parse the comand line arguments. I'm sure this can be done better,
    // especially in a parallel enviroment but, I'm tierd and want bed:)
    if ( argc > 1 )
    {
        // Loop though all the arguments if more than on is present.
        for ( int a=1; a<argc; a++ )
        {
            // checks for -i and a convertable int value.
            if ( !strcmp(argv[a],"-i") && (argc-1) > a && strtol( argv[a+1], NULL, 10 ) )
            {
                n = strtol( argv[2], NULL, 10 );
                // Ensure n is even and pass the loop over the int value.
                if ( n%2 != 0 )
                    n++;
                a++;
            }
            // checks for verbose flags.
            else if ( !strcmp(argv[a],"-v") || !strcmp(argv[a],"--verbose") )
                verbose = 1;
            else
            {
                if (my_rank == 0)
                {
                    printf("==> Invalid arguments\n");
                    printf("Usage: cmd {-i [int],-v,--verbose}\n");
                    break;
                }
            }
        }
    }

    // Dertrimine the interval of integration for n bins. ( Common to all ps ).
    h = (b-a)/n;    
    // Determine the number of bins in the interval of each p.
    local_n = n/p;  

    /* Length of each process' interval of
     * integration = local_n*h.  So my interval
     * starts at: */
    local_a = a + my_rank*local_n*h;
    local_b = local_a + local_n*h;
    integral = simpson(local_a, local_b, local_n, h);

    /* 
     * Sum the individual regions with a linear reduce. Each p sends it's
     * total to p-1 and p0 prints the results. Taken from my Paralled Trap
     * code.
     */
    // p0 only receives from p1.
    if (my_rank == 0)  
    {
        source = 1;
        MPI_Recv( &total, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status );
        total = total + integral;
    }
    // process p only sends to the next process.
    else if ( my_rank == ( p - 1 ) )
    {
        dest = my_rank - 1;
        MPI_Send( &integral, 1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD );
    }
    // everybody else in between p and p0 recvs, adds, and sends.
    else 
    {  
        source = my_rank + 1;
        dest   = my_rank - 1;
        MPI_Recv( &total, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status );
        total = total + integral;
        MPI_Send( &total, 1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD );
    }

    // Concludeing output by Process zero. My concludeing output is I'm at UI.
    if ( my_rank == 0 )
    {
        // Handle the output of the p's partitions if verbose switch set.
        if ( verbose == 1 )
        {
            // Handle the initial process.
            printf("Process 0: [ 1 ");
            for( int t=1; t<local_n; t++ )
            {
                if ( t%2 == 0 )
                    printf("2 ");
                else
                    printf("4 ");
            }
            printf("]\n");
            // Handle the intermediat Processes.
            for ( int z=1; z < p-1; z++ )
            {
                printf("Process %d: [ ",z);
                for( int t=0; t<local_n; t++ )
                {
                    if ( t%2 == 0 )
                        printf("2 ");
                    else
                        printf("4 ");
                }
                printf("]\n");
            }
            // Handle the last process.
            printf("Process %d: [ ",p-1);
            for( int t=0; t<local_n-1; t++ )
            {
                if ( t%2 == 0 )
                    printf("2 ");
                else
                    printf("4 ");
            }
            printf("1 ]\n");
        }
        printf("With n = %d trapezoids, our estimate\n", n);
        printf("of the integral from %f to %f = %f\n", a, b, total);
    }

    /* Shut down MPI */
    MPI_Finalize();
}
