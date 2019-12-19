/******************************************************
* Author : Shyam Bhuptani 
* Function : weighted_coefficient
* Application : This function uses the elimination array and 
* provides the respective weights for each elements.
* Input : elimination array(n),number of sensors
* Output : weight array of size n
*/

/*Including dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include "../../include/weight_coefficient.h"


double *find_weight_coefficient(double elimination_matrix[], int n){
    double sum_value = 0;
    /*Allocating memory for the output array*/
    double *weights = (double *) malloc(n * sizeof(double *));
    /*Calculating sum value using the elimination array*/ 
    for(int i = 0; i < n; i++){
        sum_value += elimination_matrix[i];
    }
    /*Updating the weights to the output array*/
    for(int j = 0; j < n; j++){
        weights[j] = elimination_matrix[j] / sum_value;
    }
    return weights;
}