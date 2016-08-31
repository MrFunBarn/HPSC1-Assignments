/* 
 * Brandon Bell
 * csci4576
 * hw2 8-31-2016
 *
 * Part 3a: PPMPI 4.7.2-a Simpsons Rule Serial Program.
 */

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
   float p;
   float q;
   float r;
   
   // Loop through the local_n strips in the region of integration.
   for ( int i=0; i<(local_n - 1); i++ )
   {
        p *= (i + 1);
        integral = ( h / 3 ) * ( f(local_a) + 4(mid_point) + f(local_b) );
   }
}

int main(int argc, char** argv) 
{
    int h;
    int 
}
