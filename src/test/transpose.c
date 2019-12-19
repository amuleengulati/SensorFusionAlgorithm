/** 
 * @file transpose.c
 * @author Amuleen Gulati
 * @date 7 Dec 2019
 * @brief Computes the transpose of the input matrix
 */

#include "..\..\include\transpose.h"

/**
 * \fn double** transpose(double** matrix, int n)
 * @param[in] matrix 2-D matrix whose transpose is required.
 * @param[in] n Integer value indicating size of the input matrix.
 * @brief This function computes the transpose of a given nXn matrix.
 */
    
double** transpose(double** matrix, int n){
    /*! \brief Create a matrix to store the transpose and allocate memory to it.
     */ 
    double** matrix_t;
    matrix_t = (double**) malloc(n*sizeof(double));
    for(int r = 0;r < n; r++){
        matrix_t[r] = (double*) malloc(n*sizeof(double));
    }

    /*! \brief Create a GSL matrix.
     */
    gsl_matrix* m = gsl_matrix_alloc(n,n);

    /*! \brief Assign sample values to matrix.
     */
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            gsl_matrix_set(m, i, j, matrix[i][j]);
        }
    }

    /*! \brief Call the GSL transpose function.
     */
    gsl_matrix_transpose(m);

    /*! \brief Assign the GSL transpose matrix to the created matrix.
     */
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrix_t[i][j] = gsl_matrix_get(m, i, j);
        }
    }

    /*! \brief Return the transpose.
     */
    return matrix_t;
}
