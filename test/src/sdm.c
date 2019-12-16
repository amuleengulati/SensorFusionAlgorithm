/******************************************************
* Author : Shyam Bhuptani 
* Function : Support Degree Matrix 
* Application : This function converts the input array[N] (the array of various 
* temprature) into a SDM matrix of which is having degre N*N
* Input : size of temprature array N as integer and temprature[N] of integers 
* Output : N*N support degree matrix
*/

#include "..\include\sdm.h"

/*Function declaration which returns a 2D array */
double ** support_degree_matrix(int n, double temprature[n]){
    /*Allocation of dynamic memory to the 2D output array using malloc*/
    double **sdm_matrix = (double **) malloc(n * sizeof(double *)); 
    for (int i = 0; i < n; i++){ 
        sdm_matrix[i] = (double*) malloc(n * sizeof(double));
    }

   /*Computation of SDM matrix elements as per requirement*/
    for(int x = 0; x < n; x++){
        for(int y = 0; y < n; y++){
            sdm_matrix[x][y] = exp(-((temprature[x] > temprature[y]) ? (temprature[x] - temprature[y]) : (temprature[y] - temprature[x])));
        }
    }
return sdm_matrix;
}