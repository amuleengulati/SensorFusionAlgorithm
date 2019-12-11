/******************************************************
* Author : Shyam Bhuptani 
* Function : Support Degree Matrix 
* Application : This function converts the input array[N] (the array of various 
* sensor readings) into a SDM matrix of which is having degre N*N
* Input : size of sensor readings array N as integer and sensor_readings[N] of doubles 
* Output : N*N support degree matrix
*/

/*Including dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/support_degree_matrix.h"

/*Function declaration which returns a 2D array */
double ** build_support_degree_matrix(double sensor_readings[], int n)
{
   /*Allocation of dynamic memory to the 2D output array using malloc*/
   double **sdm_matrix = (double **) malloc(n * sizeof(double *)); 
   for (int i = 0; i < n; i++) 
      sdm_matrix[i] = (double *)malloc(n * sizeof(double));
 
   /*Computation of SDM matrix elements as per provided equation*/
   for(int x = 0; x < n; x++){
      for(int y = 0; y < n; y++){
         sdm_matrix[x][y] = exp(-fabs(sensor_readings[x] - sensor_readings[y]));
      }
   }

    return sdm_matrix;
}