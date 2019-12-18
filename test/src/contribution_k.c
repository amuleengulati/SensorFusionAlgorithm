/** 
 * @file contribution_k.c
 * @author Amuleen Gulati
 * @date 16 Dec 2019
 * @brief Computes contribution rate of first k principal  
 * components.
 */

#include "..\include\contribution.h"

/**
 * \fn double* contribution_k(int n, double* D)
 * @param[in] n Integer value indicating size of the input matrix.
 * @param[in] D vector containing the eigen values of the SDM matrix.
 * @return psi 1Xn vector containing contribution rates of m principal components. 
 * @brief This function computes the contribution values.
 */
double* contribution_k(int n, double* D){

    /*! \brief Compute the sum of eigen_value vector.
     */
    double sum = 0.0;
    for(int i=0;i<n;i++){
        sum += D[i];
    }

    /*! \brief Compute the contribution rate of kth principal 
     *         component
     */
    double* alpha;
    alpha = (double*) malloc(n*sizeof(double));
    for(int k=0;k<n;k++){
        alpha[k] = D[k]/sum;
    }
    return alpha;
}