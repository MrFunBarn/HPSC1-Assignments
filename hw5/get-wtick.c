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
    int        tag = 0;
    double     start;
    double     end;
    MPI_Status status;

    // Spin-up Mpi.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    
    start = MPI_Wtime();

    double tick = MPI_Wtick();
    printf("The tick is %15.8f\n", tick);

    end = MPI_Wtime();

    printf("start %15.6f, end %15.6f\n", start, end );
    printf("The elapsed time was %15.6f\n", (end - start) );

    // Close up.
    MPI_Finalize();
    return 0;
}
