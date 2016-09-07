/* 
 * Brandon Bell
 * csci4576
 * hw3 9-7-2016
 *
 * Homework 3: Broadcast, Reduce, AllReduce.
*/

#include <stdio.h>
#include <string.h>
#include "mpi.h"

int MyPI_Bcast (
                 void*          message, 
                 int*           count,
                 MPI_Datatype   datatype, 
                 int            root,
                 MPI_Comm       comm,
                 int            bitOrder
                )
{
    // Determine the number of stages required for the tree.
    // I'm nabbing the Ceiling_log2() algorythim form chapter 5 in the book to
    // handle this.
    int p;
    int my_rank;
    MPI_Status  status;
    MPI_Comm_size ( comm, &p );
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    unsigned int stages      = 0;
    unsigned int temp   = (unsigned) p - 1;
    unsigned int companion;

    while ( temp != 0 )
    {
        temp   = temp >> 1;
        stages = stages + 1;
    }

    // Re-map Mpi rank into a rankspace where rank 0 is the root. The broadcast
    // algorythm is based an bit arithmatic for a root with value zero and this
    // process zero must have the data beinf broadcast so, re-map the mpi rank
    // to root = rank zero with modulo arithmatic, the ultimate mapping is
    // irrelevant ( I think) as long as it is consitent and the new rank zero
    // has the messsage to be sent.

    int rank = ( my_rank + ( p - root ) ) % p;
    int mpirank = ( rank + ( p + root ) ) % p;

    // Set up the loop to determine send and recvs for each stage of the tree.
    // This is for low to high bit method.
    for ( int stage = 0; stage < stages; stage++ )
    {
        // Determine the current processes send/Recev companion.
        companion = ( 1 << stage ) ^ rank;
        
        // Detremine wheither to send/recv or do nothing with it's companion.
        // First determine if p is to recv at this stage.
        if ( ( rank > companion ) && ( companion >> ( 1 << stage ) ) == 0 )
        {
            int mpirank = ( companion + ( p + root ) ) % p;
            MPI_Recv( message, count, MPI_FLOAT, my_rank, 1, comm, &status );
            printf("Step %d rank %d Recvs from %d\n", stage, my_rank, companion);
        }
        // Or if p is suposed to send at this stage.
        else if ( ( rank < companion ) && ( companion >> ( 1 << stage ) ) == 0 )
        {
            int mpirank = ( companion + ( p + root ) ) % p;
            MPI_Send( message, count, MPI_FLOAT, my_rank, 1, comm );
            printf("Step %d rank %d Sends to %d\n", stage, my_rank, companion);
        }
        // Handle the case that P and it's companion are not to communicate
        // during this stage.
        else
            int mpirank = ( companion + ( p + root ) ) % p;
            printf("Step %d rank %d does nothing\n", stage, mpirank);
            continue;
    }
    return message;
}

void MyPI_Reduce (
                  void*         operand,
                  void*         result,
                  int           count,
                  MPI_Datatype  datatype,
                  MPI_Op        operator,
                  int           root,
                  MPI_Comm      comm,
                  int           bitOrder
                  )
{
}

void MyPI_AllReduce (
                     void*          operand,
                     void*          result,
                     int            count,
                     MPI_Datatype   datatype,
                     MPI_Op         operator,
                     int            root,
                     MPI_Comm       comm,
                     int            bitOrder
                     )
{
}

void MyPI_AllReduce_Trivial (
                             void*          operand, 
                             void*          result, 
                             int            count, 
                             MPI_Datatype   datatype, 
                             MPI_Op         operator, 
                             int            root, 
                             MPI_Comm       comm,
                             int            bitOrder
                             )
{
}

int main ( int argc, char* argv[] )
{
    int         my_rank;   
    int         p;         
    int         source;    
    int         dest;      
    int         tag = 0;
    float       message;
    MPI_Status  status;

    // Spin-up Mpi.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // Check to make sure that more than process are running.
    if ( p == 1 )
    {
        printf("Please Run with > 1 processes.\n" );
        return 1;
    }

    if ( my_rank == 0 )
        message = 5;
    else
        message = 0;

    MyPI_Bcast ( &message, 1, MPI_FLOAT, 0, MPI_COMM_WORLD, 1 );

    printf("Message on rank %d is %f \n", my_rank, message );

    MPI_Finalize();
    return 0;
}
