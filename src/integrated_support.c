/** 
 * @file integrated_support.c
 * @author Shyam Bhuptani
 * @brief Computes support degree score for all the m sensors
 */
/**
 *
 * \fn compute_integrated_support(double alpha[], double principal_components[],int n)
 * \author Shyam Bhuptani
 * \brief This function provides the support degree score for all the m sensors, though total
 * number of sensors provided as input shall be as same as n, as we are making alpha 0 for psi > 85%
 * in previous stage.
 * Support degree score is calculated using the contribution rate and the principal components.
 * @param[in] size of contribution array m
 * @param[in] concontribution array(alpha)
 * @param[in] principal components(size n) 
 * @return integrated support for all m sensors in terms of 1-D matrix
 */

/*Including dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/integrated_support.h"


double *compute_integrated_support(double alpha[], double principal_components[],int n){
    /*Allocating memory for the output matrix*/
    double *integrated_support_matrix = (double *) malloc(n * sizeof(double *)); 
    for(int i = 0; i < n; i++){
        /*Each sensor's integrated support is formed using a simple multiplication of  
        alpha and principal matrix for the same sensor*/
        integrated_support_matrix[i] = alpha[i] * principal_components[i];
    }
    return integrated_support_matrix;
}