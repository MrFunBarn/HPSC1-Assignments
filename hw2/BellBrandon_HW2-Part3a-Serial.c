/* 
 * Brandon Bell
 * csci4576
 * hw2 8-31-2016
 *
 * Part 3a: PPMPI 4.7.2-a Simpsons Rule Serial Program.
 */

#include <stdio.h>

// I nabbed f from the trap program.
float f(float x) {
    float return_val;
    /* Calculate f(x). */
    /* Store calculation in return_val. */
    return_val = x*x;
    return return_val;
} 

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

int main(int argc, char** argv) 
{
    float  total;
    float  a = 0;
    float  b = 1;
    int    n = 1024;
    float  h;   

    h = (b-a)/n;    
    total = simpson( a, b, n, h );
    printf("With n = %d trapezoids, our estimate\n", n);
    printf("of the integral from %f to %f = %f\n", a, b, total);
}
