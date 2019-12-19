/** 
 * @file contribution.c
 * @author Amuleen Gulati
 * @date 1 Dec 2019
 * @brief Computes contribution rate of first m principal  * components.
 */

#include "..\include\contribution.h"

/**
 * \fn double* contribution(int n, double* D)
 * @param[in] n Integer value indicating size of the input matrix.
 * @param[in] D vector containing the eigen values of the SDM matrix.
 * @return psi 1Xn vector containing contribution rates of m principal components. 
 * @brief This function computes the contribution values.
 */
double* contribution(int n, double* D){

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

    /*! \brief Compute the contribution rate of m principal components.
     */
    double* psi;
    psi = (double*) malloc(n*sizeof(double));
    psi[0] = alpha[0];
    for(int m = 1; m < n; m++){
        psi[m] = psi[m-1] + alpha[m];
    }
    double* psi_m;
    psi_m = (double*) malloc(n*sizeof(double));
    for(int i = 0; i < n; i++){
        if(psi[i] < 0.85){
            psi_m[i] = 0;
        }
        else{
            psi_m[i] = psi[i];
        }
    }
    return psi_m;
}