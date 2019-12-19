/** 
 * @file multiply.c
 * @author Amuleen Gulati
 * @date 3 Dec 2019
 * @brief Computes the product of two vectors
 */

#include "..\..\include\multiply.h"

/**
 * \fn double multiply(double* eigen_vector, double* eigen_value)
 * @param[in] eigen_vector a single eigen vector of the input matrix.
 * @param[in] eigen_value a vector containing eigen values of the input matrix.
 * @param[in] n integer containing size of vectors. 
 * @brief This function computes the vector product.
 */

double multiply(double* eigen_vector, double* eigen_value, int n){
    double sum = 0.0;

    double* vector;
    vector = (double*) malloc(n*sizeof(double));

    /*! \brief Create two GSL vectors.
     */
    gsl_vector* v1 = gsl_vector_alloc(n);
    gsl_vector* v2 = gsl_vector_alloc(n);

    /*! \brief Assign values to vectors.
     */
    for (int i = 0; i < n; i++){
        gsl_vector_set(v1, i, eigen_vector[i]);
    }

    for (int i = 0; i < n; i++){
        gsl_vector_set(v2, i, eigen_value[i]);
    }

    /*! \brief Call GSL vector multiplication function.
     */
    gsl_vector_mul(v1,v2);

    /*! \brief Assign the matrix multipliction result to a vector.
     */
    for (int i = 0; i < n; i++){
        vector[i] = gsl_vector_get(v1, i);
        sum += vector[i];
    }
    return sum;
}