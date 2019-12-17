/** 
 * @file auto_unit_test.c
 * @author Amuleen Gulati
 * @date 15 Dec 2019
 * @brief Handles unit testing of individual files.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

/*! \brief Include all dependencies.
 */
#include "..\lib\gsl\eigen\gsl_eigen.h"
#include "..\lib\gsl\gsl_math.h"

#include "..\include\sdm.h"
#include "..\include\multiply.h"
#include "..\include\transpose.h"
#include "..\include\eigen.h"
#include "..\include\principle_comp.h"
#include "..\include\contribution.h"
#include "..\include\parse.h"

#define DELIMITER ","
#define MAX_ENTRIES 100
#define MAX_LINE_SIZE 128

int main(){
    /*! \brief Declare a variable n to store the number of sensor entries with same time values. 
     */
    int n = 2;

    /*! \brief Take a sample 2X2 array to test different files.
     */
    double** input_array;
    input_array = (double**) malloc(2*sizeof(double));
    for(int r = 0; r < 2; r++){
        input_array[r] = (double*) malloc(2*sizeof(double));
    }
    input_array[0][0] = 10.0;
    input_array[0][1] = 20.0;
    input_array[1][0] = 30.0;
    input_array[1][1] = 30.5;

    /***********************************************AUTOMATIC UNIT TESTING****************************************************/
    
    printf("*********************UNIT TESTING OF FUNCTIONS****************************\n\n");
    printf("**************************************************************************\n\n");
    printf("Testing eigen vector function using the array [10.0, 20.0, 30.0, 30.5]\n");

    /**
     * \fn double** eigen_vector(int n, double** D)
     * @param[in] n Integer value indicating size of the matrix.
     * @param[in] D 2-D array containing the support degree matrix values.
     * @brief This function computes the eigen vectors for an array of size nXn.
     */
    double** e_vectors;
    e_vectors = (double**) malloc(2*sizeof(double));
    for(int r = 0; r < 2; r++){
        e_vectors[r] = (double*) malloc(2*sizeof(double));
    }
    e_vectors = eigen_vector(2, input_array);
    printf("Expected output for eigen vectors: [0.813424 0.581672 -0.581672 0.813424]\n");
    printf("Eigen vector values obtained from eigen_vector.c: [");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("%f ", e_vectors[i][j]);
        }
    }
    printf("]\n\n"); 

    printf("**************************************************************************\n\n");
    printf("Testing eigen value function using the array [10.0, 20.0, 30.0, 30.5]\n");

    /**
     * \fn double* eigen_value(int n, double** D)
     * @param[in] n Integer value indicating size of the input matrix.
     * @param[in] D 2-D array containing the support degree matrix values.
     * @brief This function computes the eigen values for an array of size nXn.
     */
    
    double* e_values;
    e_values = (double*) malloc(2*sizeof(double));
    e_values = eigen_value(2, input_array);
    printf("Expected output for eigen values: [-11.4527 51.9527]\n");
    printf("Eigen vector values obtained from eigen_value.c: [");
    for(int i = 0; i < 2; i++){
            printf("%f ", e_values[i]);
    }
    printf("]\n\n"); 

    printf("**************************************************************************\n\n");
    printf("Testing multiply function using the array [10.0, 20.0, 30.0, 30.5]\n");

    /**
     * \fn double multiply(double* eigen_vector, double* eigen_value)
     * @param[in] eigen_vector a single eigen vector of the input matrix.
     * @param[in] eigen_value a vector containing eigen values of the input matrix.
     * @brief This function computes the vector product.
     */
    
    double product;
    
    /*! \brief Take a sample 1X2 eigen vector
     */
    double* sample_e_vector;
    sample_e_vector = (double*) malloc(2*sizeof(double));
    sample_e_vector[0] = 0.813424;
    sample_e_vector[1] = 0.581672;

    product = multiply(sample_e_vector, e_values);
    printf("Expected output for product: 20.9035\n");
    printf("Product obtained from mutiply.c: %f\n\n", product);

    printf("**************************************************************************\n\n");
    printf("Testing transpose function using the array [10.0, 20.0, 30.0, 30.5]\n");

    /**
     * \fn double** transpose(double** matrix, int n)
     * @param[in] matrix 2-D matrix whose transpose is required.
     * @param[in] n Integer value indicating size of the input matrix.
     * @brief This function computes the transpose of a given nXn matrix.
     */
    
    double** matrix_transpose;
    matrix_transpose = (double**) malloc(2*sizeof(double));
    for(int r = 0; r < 2; r++){
        matrix_transpose[r] = (double*) malloc(2*sizeof(double));
    }

    matrix_transpose = transpose(input_array, 2);
    printf("Expected output for transpose: [10.0 30.0 20.0 30.5] \n");
    printf("Transpose obtained from transpose.c: [");
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("%f ", matrix_transpose[i][j]);
        }
    }
    printf("]\n\n"); 

    printf("**************************************************************************\n\n");
    printf("Testing principal component function using the array [10.0, 20.0, 30.0, 30.5]\n");

    /**
     * \fn double* principle_component(int n, double** D, double* T)
     * @param[in] n Integer value indicating size of the input matrix.
     * @param[in] D vector containing the eigen values of the SDM matrix.
     * @param[in] T 2-D array containing the eigen vector values of the SDM matrix.
     * @brief This function computes the principal component values.
     */
    
    double* p_components;
    p_components = (double*) malloc(2*sizeof(double));
    p_components = principle_component(2, e_vectors, e_values);
    printf("Expected output for principal component values: [20.9035 48.9212]\n");
    printf("Principal component values obtained from principle_comp.c: [");
    for(int i = 0; i < 2; i++){
            printf("%f ", p_components[i]);
    }
    printf("]\n\n"); 

    printf("**************************************************************************\n\n");
    printf("Testing contribution function using the array [10.0, 20.0, 30.0, 30.5]\n");

    /**
     * \fn double* contribution(int n, double* D)
     * @param[in] n Integer value indicating size of the input matrix.
     * @param[in] D vector containing the eigen values of the SDM matrix.
     * @brief This function computes the contribution values.
     */
    
    double* c_values;
    c_values = (double*) malloc(2*sizeof(double));
    c_values = contribution(2, e_values);
    printf("Expected output for contribution values: [-0.2827]\n");
    printf("Contribution values obtained from contribution.c: [");
    for(int i = 0; i < 1; i++){
            printf("%f ", c_values[i]);
    }
    printf("]\n\n"); 
    printf("**************************************************************************\n\n");

    return 0;
}
