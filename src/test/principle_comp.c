/** 
 * @file principle_comp.c
 * @author Amuleen Gulati
 * @date 7 Dec 2019
 * @brief Computes the principle component values for the input
 *  eigen values and eigen vectors.
 */

#include "..\..\include\principle_comp.h"
#include "..\..\include\transpose.h"
#include "..\..\include\multiply.h"

/**
 * \fn double* principle_component(int n, double** D, double* T)
 * @param[in] n Integer value indicating size of the input matrix.
 * @param[in] D vector containing the eigen values of the SDM matrix.
 * @param[in] T 2-D array containing the eigen vector values of the SDM matrix.
 * @brief This function computes the principal component values.
 */

double* principle_component(int n, double** D, double* T){

    /*! \brief Create a vector to store principal component values.
     */
    double* y;
    y = (double*) malloc(n*sizeof(double));

    /*! \brief Create a vector to store individual eigen vectors.
     */
    double* eigen_vector;
    eigen_vector = (double*) malloc(n*sizeof(double));

    /*! \brief Create a matrix to store the values.
     */
    double** matrix;
    matrix = (double**) malloc(n*sizeof(double));
    for(int r = 0;r < n;r++){
        matrix[r] = (double*) malloc(n*sizeof(double));
    }

    /*! \brief Create a GSL matrix.
     */
    gsl_matrix* m = gsl_matrix_alloc(n,n);

    /*! \brief Assign sample values to GSL matrix and fill the matrix.
     */
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            gsl_matrix_set(m, i, j, D[i][j]);
            matrix[i][j] = gsl_matrix_get(m, i, j);
        }
    }

    /*! \brief Call transpose function.
     */
    matrix = transpose(matrix, n);

    /*! \brief Modify GSL matrix to contain transposed values.
     */ 
    for(int i = 0;i < n;i++){
        for(int j = 0;j < n;j++){
            gsl_matrix_set(m, i, j, matrix[i][j]);
        }
    }

    /*! \brief Create vertical splits of matrix to access individual eigen vectors.
     */
    for(int i=0;i<n;i++){
        gsl_vector_view v = gsl_matrix_column(m,i);
        for(int j=0;j<n;j++){
            eigen_vector[j] = gsl_vector_get(&v.vector,j);
        }
    y[i] = multiply(eigen_vector, T, n);
    }
    return y;
}
