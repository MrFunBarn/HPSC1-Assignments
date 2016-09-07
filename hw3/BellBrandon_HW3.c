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

void MyPI_Bcast (
                 void*          message, 
                 int            count,
                 MPI_Datatype   datatype,
                 int            root,
                 MPI_Comm       comm,
                 int            bitOrder
                )
{
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
    MPI_Status  status;

    // Spin-up Mpi.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

}
