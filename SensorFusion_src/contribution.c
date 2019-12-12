/***************************************************************************
* Author : Shyam Bhuptani 
* Function : Contribution 
* Application : This function takes the eigenvalues and returns the alpha
* Input : size of eigenvalues n, eigenvalue array (lambda) of size n
* Output : alpha is an array of size n
*/

/*Including dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/contribution.h" 

double * compute_contributions(double lambda[], int n)
{
    double sum = 0;
    double * contribution_array = (double *)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++){
        sum += lambda[i];
    }
   /*Computation contribution by weighing the lambda using sum value*/
    for(int j = 0; j < n; j++){
        contribution_array[j] = lambda[j] / sum;
    }

    return contribution_array;
}