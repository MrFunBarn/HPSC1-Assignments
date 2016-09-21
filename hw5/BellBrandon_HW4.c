/* 
 * Brandon Bell
 * csci4576
 * hw5 9-21-2016
 *
 * Homework 5: Alpha-Beta, Dense Matrix Transform. 
*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
    int        my_rank;
    int        p;
    int        tag    = 0;
    double     start;
    double     tick;
    double     end;
    int        np     = 100000;
    int        msize  = 100;
    char       message[msize];
    double     total;
    char       name[MPI_MAX_PROCESSOR_NAME];
    int        pnamemax;
    MPI_Status status;

    // Spin-up Mpi.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    // Get the node name for output.
    MPI_Get_processor_name(name,&pnamemax);

    // Ensure that the needed 2 processes for a ping pong test are there and no
    // more.
    if( p != 2 )
    {
        printf("Please use exactly 2 processes");
        return 1;
    }

    // Loop through a series of pingpong passes with Wtime calls on either side
    // of the loop to get the time for np passes.
    end = 0;

    // Dump out each rank and the node that it's on.
    fflush(stdout);
    printf("[ %s, %d ]\n", name, my_rank);

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
    {
        end = MPI_Wtime();
        // calculate average message time for np messages, then the 1/2 round
        // trip time.
        total = (end - start); 
        total = total / np;
        total = total / 2;
        // Output the timing [ name , rank ], start, end, single size, message
        // size.
        printf("[ %s, %d ], %5.10f, %5.10f, %1.15f, %4d\n", name, my_rank, start, end, total, msize);
    }

    // Close up.
    MPI_Finalize();
    return 0;
}
