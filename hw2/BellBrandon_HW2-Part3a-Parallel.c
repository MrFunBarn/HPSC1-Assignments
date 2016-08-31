/* 
 * Brandon Bell
 * csci4576
 * hw2 8-31-2016
 *
 * Part 3a: PPMPI 4.7.2-a Simpsons Rule Serial Program.
 */

#include <stdio.h>
#include <string.h>

// I nabbed f from the trap program.
float f(float x) {
    float return_val;
    /* Calculate f(x). */
    /* Store calculation in return_val. */
    return_val = x*x;
    return return_val;
} 

// I nabbed simpson from my serial code.
float simpson (
          float  a   /* in */,
          float  b   /* in */,
          int    n   /* in */,
          float  h   /* in */) 
{
   float integral; 
   float x = a;
   
   // Take care of the starting and end points.
   integral = f(a) + f(b);
   // Loop through the n strips in the region of integration.
   for ( int i=1; i<(2*n - 1); i++ )
   {
        // increment x by a half interval at a time (we need the mid point).
        x += h / 2;
        if ( i % 2 == 0 )
            integral += ( 2 * f(x) );
        else 
            integral += ( 4 * f(x) );
   }
   integral *= ( h / 3 );
   return integral;
}

// Most of my main is addapted from the Parallel Trap Code.
int main(int argc, char** argv) 
{
    int         my_rank;   /* My process rank           */
    int         p;         /* The number of processes   */
    float       a = 0.0;   /* Left endpoint             */
    float       b = 1.0;   /* Right endpoint            */
    int         n = 1024;  /* Number of trapezoids      */
    float       h;         /* Trapezoid base length     */
    float       local_a;   /* Left endpoint my process  */
    float       local_b;   /* Right endpoint my process */
    int         local_n;   /* Number of trapezoids for  */
                           /* my calculation            */
    float       integral;  /* Integral over my interval */
    float       total;     /* Total integral            */
    int         source;    /* Process sending integral  */
    int         dest;      /* All messages go to 0      */
    int         tag = 0;
    MPI_Status  status;

    // Initial MPI and retreive world size and p's rank.
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    // Dertrimine the interval of integration for n bins. ( Common to all ps ).
    h = (b-a)/n;    
    total = simpson( a, b, n, h );
    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %f\n", a, b, total);
}
