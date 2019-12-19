/** 
 * @file eigen_vector.c
 * @author Amuleen Gulati
 * @date 2 Dec 2019
 * @brief Computes the eigen vectors matrix having degree  
 * n*n for the input sd_matrix[n][n] (the SDM matrix) .
 */

#include "..\..\include\eigen.h"

/**
 * \fn double** eigen_vector(int n, double** D)
 * @param[in] n Integer value indicating size of the matrix.
 * @param[in] D 2-D array containing the support degree matrix values.
 * @brief This function computes the eigen vectors for an array of size nXn.
 */

double** eigen_vector(int n, double** D){

    /*! \brief Initialize an nXn matrix to store eigen vectors.
     */ 
    double** evector;
    evector = (double**) malloc(n*sizeof(double));  
    for(int r = 0;r < n;r++){
        evector[r] = (double*) malloc(n*sizeof(double));
    }

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

    /*! \brief Assign the computed eigenvectors to the evector matrix.
     */
    for (int i = 0; i < n; i++){
        for(int j = 0;j < n;j++){
	    evector[i][j] = gsl_matrix_get(evecs, i, j);
        }
    }

    /*! \brief Free the GSL memory.
     */
    gsl_eigen_symmv_free(workspace);
    gsl_matrix_free(M);
    gsl_matrix_free(evecs);
    gsl_vector_free(evals);

    return evector;
}