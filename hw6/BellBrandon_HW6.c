/* 
 * Brandon Bell
 * CSCI: 4576
 * HW6: Parallel Matrix Multiplication Using Fox's Algorythm
 * 9-28-16
 *
 */

// TO-DO:
//
// 1) Needed for Assignment. Make p.83 code into a matrix-matrix pruduct via n
// allgathers on on the columns and doing the dots.
//
// - Local_matrix?
//
// 2) Implement Fox's for square matricies. Can get matricies however.

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mpi.h"

// Paralell matrix code from p.83.
void Paralled_matrix_matrix_prod(
//                                 LOCAL_MATRIX_T     local_A,
                                 int                m,
                                 int                n,
                                 float              local_x[],
                                 float              global_x[],
                                 float              local_y[],
                                 int                local_m,
                                 int                local_n )
{
    // local_m = m/p, local_n = n/p
    
    int i;
    int j;

    /* MPI_Allgather( local_x, local_n, MPI_FLOAT, global_x, local_n, MPI_FLOAT, MPI_COMM_WORLD ); */
/*  */
    /* for ( i=0; i<local_m, i++ ) */
        /* local_y[i] = local_y[i] + local_A[i][j]*global_x[j]; */
}

/* // Serial Matrix Vector Product from p.78. */
/* void serial_matrix_vector_prod( */
                                /* MATRIX_T    A; */
                                /* int         m; */
                                /* int         n; */
                                /* float       x[]; */
                                /* float       y[];) */
/* { */
    /* int     k; */
    /* int     j; */
/*  */
    /* for ( k = 0; j<n; j++ ) */
    /* { */
        /* y[k] = 0.0; */
        /* for ( j = 0; j<n; j++ ) */
            /* y[k] = y[k] + A[k][j]*x[j]; */
    /* } */
/* } */

int main( int argc, char* argv[] )
{
}
