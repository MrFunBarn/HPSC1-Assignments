/****************************************************************************
 * Michael Oberg
 * 12/04/2004
 * Purpose: Find out the size of the different data types
 ****************************************************************************/
#include <stdio.h>
#include "mpi.h"

int main(int argc, char* argv[])
{
  /*
   * int/char   are 'type specifiers'
   * short/long are 'type qualifiers'
   */
  int i;
  printf("    short int is %2d bytes \n", sizeof(short int));
  printf("          int is %2d bytes \n", sizeof(int));
  printf("        int * is %2d bytes \n", sizeof(int *));
  printf("     long int is %2d bytes \n", sizeof(long int));
  printf("   long int * is %2d bytes \n", sizeof(long int *));
  printf("   signed int is %2d bytes \n", sizeof(signed int));
  printf(" unsigned int is %2d bytes \n", sizeof(unsigned int));
  printf("\n");
  printf("        float is %2d bytes \n", sizeof(float));
  printf("      float * is %2d bytes \n", sizeof(float *));
  printf("       double is %2d bytes \n", sizeof(double));
  printf("     double * is %2d bytes \n", sizeof(double *));
  printf("  long double is %2d bytes \n", sizeof(long double));
  printf("\n");
  printf("  signed char is %2d bytes \n", sizeof(signed char));
  printf("         char is %2d bytes \n", sizeof(char));
  printf("       char * is %2d bytes \n", sizeof(char *));
  printf("unsigned char is %2d bytes \n", sizeof(unsigned char));
  printf("\n");
  printf("       void * is %2d bytes \n", sizeof(void *));

  // Spin-up Mpi.
  MPI_Init(&argc, &argv);
  double tick = MPI_Wtick();
  printf("The tick is %15.8f\n", tick);
  MPI_Finalize();
}

