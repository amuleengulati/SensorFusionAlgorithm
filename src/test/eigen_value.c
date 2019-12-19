/** 
 * @file eigen_value.c
 * @author Amuleen Gulati
 * @date 2 Dec 2019
 * @brief Computes the eigen values vector having degree n for 
 * an input matrix[n][n] (the SDM matrix)
 */

#include "..\..\include\eigen.h"

/**
 * \fn double* eigen_value(int n, double** D)
 * @param[in] n Integer value indicating size of the input matrix.
 * @param[in] D 2-D array containing the support degree matrix values.
 * @brief This function computes the eigen values for an array of size nXn.
 */

double* eigen_value(int n, double** D){
    /*! \brief Initialize an array to store eigen values.
     */
    double* evalue;
    evalue = (double*) malloc(n*sizeof(double));

    /*! \brief Create a GSL matrix M.
     */
    gsl_matrix* M = gsl_matrix_alloc(n, n);

    /*! \brief Assign the elements of Matrix.
     */
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            gsl_matrix_set(M, i, j, D[i][j]);
        }
    }

    /*! \brief Create a GSL matrix to store eigenvectors.
     */
    gsl_matrix* evecs = gsl_matrix_alloc(n,n);

    /*! \brief Create a GSL vector to store eigenvalues.
     */
    gsl_vector* evals = gsl_vector_alloc(n);

    /*! \brief Initialize an eigen workspace.
     */
    gsl_eigen_symmv_workspace* workspace = gsl_eigen_symmv_alloc(n);

    /*! \brief Compute the eigenvalues and eigenvectors.
     */
    gsl_eigen_symmv(M, evals, evecs, workspace);

    /*! \brief Assign the computed eigenvalues to the evalues vector.
     */
    for (int i = 0; i < n; i++){
        evalue[i] = gsl_vector_get(evals, i);
    }
    return evalue;
}