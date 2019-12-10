/******************************************************
* Author : Shyam Bhuptani 
* Function : Support Degree Matrix 
* Application : This function converts the input array[N] (the array of various 
* temprature) into a SDM matrix of which is having degre N*N
* Input : size of temprature array N as integer and temprature[N] of integers 
* Output : N*N support degree matrix
*/

/*Including dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/Support_Degree_Matrix.h"

/*Function declaration which returns a 2D array */
double ** Support_Degree_Matrix(int n, int temprature[n])
{
   int i = 0, x = 0, y = 0;
   /*Allocation of dynamic memory to the 2D output array using malloc*/
   double **SDM_MATRIX = (double **) malloc(n * sizeof(double *)); 
   for (i=0; i<n; i++) 
      SDM_MATRIX[i] = (double *)malloc(n * sizeof(double));

   /*Computation of SDM matrix elements as per requirement*/
   for(x = 0;x < n; x++){
      for(y = 0;y < n; y++){
         SDM_MATRIX[x][y] = exp(-((temprature[x] > temprature[y]) ? (temprature[x] - temprature[y]) : (temprature[y] - temprature[x])));
      }
   }

    return SDM_MATRIX;
}