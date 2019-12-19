/** 
 * @file elimination.c
 * @author Shyam Bhuptani
 * @brief Eliminates components which fails specific condition
 */
/**
 *
 * \fn elimination_of_integrated_support(double integrated_support[], int n)
 * \author Shyam Bhuptani
 * \brief This function uses the support degree score for all the sensors to 
 * determine the correctness using the standard formula where each sensors score should be
 * greater than (average score * 0.7), otherwise it will be disregarded.
 * @param[in] integrated support array(n)
 * @param[in] total number of sensors
 * @return integrated support for all j sensors who passed the condition and rest are set to 0
 */

/*Including dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/elimination.h"


double *elimination_of_integrated_support(double integrated_support[], int n){
    double average_value;
    /*Allocating memory for the output matrix*/
    double *elimination_matrix = (double *) malloc(n * sizeof(double *));
    /*Calculating Average value of the integrated support*/ 
    for(int i = 0; i < n; i++){
        average_value += integrated_support[i]/n;
    }
    /*Checking the condition and updating new values after elimination*/
    for(int j = 0; j < n; j++){
        if(integrated_support[j] > (average_value * 0.7)){
            elimination_matrix[j] = integrated_support[j];
         }
         else{
             /*If value does not satisfy above condition then putting it as 0,
             as we cannot reduce the array size. the reason behind is if we reduce array size
             it will make issue while computing the fused output in final step
			 as the input array x is of size n and the mismatch of length 
			 can produce falsy result*/
             elimination_matrix[j] = 0; 
         }
    }
    return elimination_matrix;
}