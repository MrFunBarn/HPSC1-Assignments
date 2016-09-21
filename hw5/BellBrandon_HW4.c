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
    int        np     = 10000;
    int        msize  = 0;
    int        maxpower = 20;
    int        maxsize = pow(2,maxpower)*4;
    char       message[maxsize];
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
        fflush(stdout);
        printf("[ %s, %d ], Please use exactly 2 processes\n", name, my_rank);
        return 1;
    }

    // Dump out each rank and the node that it's on.
    fflush(stdout);
    printf("[ %s, %d ]\n", name, my_rank);

    // Loop through a series of pingpong passes with Wtime calls on either side
    // of the loop to get the time for np passes.
    for ( int i=0; i <= maxpower; i++ )
    {
        msize = pow(2,i);
        // Ensure process are synced at this point because p0 handles the output.
        MPI_Barrier(MPI_COMM_WORLD); 
        // Have p0 start timing
        if( my_rank == 0 )
            start = MPI_Wtime();
        for( double j=0; j < np; j++ )
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
        // p0 ends timeing, does calculations and dumps output for the np runs.
        if( my_rank == 0 )
        {
            end = MPI_Wtime();
            printf("i %d\n",i);

            // calculate average message time for np messages, then the 1/2 round
            // trip time.
            total = (end - start); 
            total = total / np;
            total = total / 2;

            // Output the timing to stdout.
            printf("[ %s, %d ], %5.10f, %5.10f, %1.15f, %4d\n", name, my_rank, start, end, total, msize);
        }
    }

    // Close up.
    MPI_Finalize();
    return 0;
}
