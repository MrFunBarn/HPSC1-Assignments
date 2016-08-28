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

     /* Setup the ring of process comunication using modulo arithimatic. First
     * check to see if p is alone in the universe and if so, just print a
     * meassage as there's no need to invoke MPI. If not, start a message
     * passing ring with process 0. p0 will send and then recive a message, all
     * other p's recive and the send. */
    if ( p == 1)
    {
        printf("Greetings from Process 0")
    }
    else if ( my_rank == 0 )
    {
        sprintf( message, "Greetings from process 0" )
    }

    // Close-up shop.
    MPI_Finalize();
}
