/* 
 * Brandon Bell
 * csci4576
 * hw2 8-24-2016
 *
 * Part 1: Ring Hello World program.
*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int main(int argc, char* argv[]) 
{
    int         my_rank;       /* rank of process      */
    int         p;             /* number of processes  */
    int         source;        /* rank of sender       */
    int         dest;          /* rank of receiver     */
    int         tag = 0;       /* tag for messages     */
    char        message[100];  /* storage for message  */
    MPI_Status  status;        /* return status for    */
                               /* receive              */

    // Initialize MPI and fetch p's rank and comm size.
    MPI_Init( &argc, &argv );
    MPI_Comm_rank( MPI_COMM_WORLD, &my_rank );
    MPI_Comm_size( MPI_COMM_WORLD, &p );

    /* Setup the ring of process comunication using modulo arithimatic */
    if ( my_rank == 0 )
    {
        sprintf( message, "Greetings from process 0" )
    }

    // Close-up shop.
    MPI_Finalize();
}
