/* 
 * Brandon Bell
 * csci4576
 * hw5 9-21-2016
 *
 * Homework 5: Alpha-Beta, Dense Matrix Transform. 
 * Part 5: Dense Matrix Transform.
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int        my_rank;
    int        p;
    int        tag     = 0;
    int        n       = 5;
    MPI_Status status;

    // Spin-up Mpi.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if ( my_rank == 0 )
    {
        // Define an upper trianglur array of 1's on P0.
        int        a[n][n];
        for( int i=0; i <= n; i++ )
        {
            for( int j=0; j <= n; j++ )
            {
               if ( j < i )
                   a[i][j] = 1;
                else 
                    a[i][j] = 0;
            }
        }

        // Print the matrix.
        for( int i=0; i <= n; i++ )
        {
            printf("| ");
            for( int j=0; j <= n; j++ )
            {
                printf("%d ", a[i][j]);
            }
            printf("|\n");
        }
    }

    // Close-Up MPI.
    MPI_Finalize();
}
