/* 
 * Brandon Bell
 * csci4576
 * hw5 9-21-2016
 *
 * Homework 5: Alpha-Beta, Dense Matrix Transform. 
*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int        my_rank;
    int        p;
    int        tag    = 0;
    double     start;
    double     tick;
    double     end;
    int        np     = 100;
    int        msize  = 1024;
    char       message[msize];
    double     total;
    MPI_Status status;

    // Spin-up Mpi.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // Loop through a series of pingpong passes with Wtime calls on either side
    // of the loop to get the time for np passes.
    end = 0;
    if( p == 2 )
    {
        // Ensure process are synced at this point.
        MPI_Barrier(MPI_COMM_WORLD); 
        // Have p0 start timing
        if( my_rank == 0 )
            start = MPI_Wtime();
        for( int i=0; i < np; i++ )
        {
            if( my_rank == 0 )
            {
                MPI_Send( &message, msize, MPI_CHAR, 1, tag, MPI_COMM_WORLD );
                MPI_Recv( &message, msize, MPI_CHAR, 1, tag, MPI_COMM_WORLD, &status );
            }   
            else 
            {
                MPI_Recv( &message, msize, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status );
                MPI_Send( &message, msize, MPI_CHAR, 0, tag, MPI_COMM_WORLD );
            }
        }
        if( my_rank == 0 )
            end = MPI_Wtime();
    }
    if( my_rank == 0 )
    {
    total = (end - start); 
    printf("%15.10f\n",total);
    total = (end - start) / 2*np; 
    printf("The elapsed time was %15.10f\n", total );
    }

    //MPI_Send( &integral, 1, MPI_FLOAT, dest, tag, MPI_COMM_WORLD );
    //MPI_Recv( &total, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, &status );

    // Close up.
    MPI_Finalize();
    return 0;
}
