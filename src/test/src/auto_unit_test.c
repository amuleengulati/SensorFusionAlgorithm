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
#include "../../../lib/gsl/eigen/gsl_eigen.h"
#include "../../../lib/gsl/gsl_math.h"

#include "../../../include/sdm.h"
#include "../../../include/multiply.h"
#include "../../../include/transpose.h"
#include "../../../include/eigen.h"
#include "../../../include/principle_comp.h"
#include "../../../include/contribution.h"
#include "../../../include/integrated_support.h"
#include "../../../include/elimination.h"
#include "../../../include/weight_coefficient.h"
#include "../../../include/fused_output.h"
#include "../../../include/parse.h"

#define DELIMITER ","
#define MAX_ENTRIES 100
#define MAX_LINE_SIZE 128

#define SDM_TEST_ARRAY_SIZE 2
#define CONTRIBUTION_TEST_ARRAY_SIZE 3
#define INTEGRATED_SUPPORT_TEST_ARRAY_SIZE 2
#define ELIMINATION_TEST_ARRAY_SIZE 4
#define WEIGHT_TEST_ARRAY_SIZE 4
#define FUSED_OP_TEST_ARRAY_SIZE 4
#define NUMBER_OF_SENSOR 3

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
    free(e_vectors);

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
    free(e_values);

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
    free(sample_e_vector);

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
    free(matrix_transpose);

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
    free(p_components);

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
    free(c_values);
    printf("**************************************************************************\n\n");

    /*******************************************************
    * Author : Shyam Bhuptani 
    * Function : Unit Testing of all Functions
    */
    
    /*Testing of Function Support Degree Matrix using one-D input array
    * This function performs (e^-(abolute(reading[i]-reading[j]))) for 2 sensors 
    * and provides results
    * @input : double array of size 2 for testing with value [10.00, 20.00]
    * @output expected : 2D array [[1.000000 0.000045] [0.000045 1.000000]]
    */
    printf("*****************************************************\n");
    printf("Testing Support degree function using array [10.00,20.00]\n");
    printf("Expected array is [[1.000000 0.000045] [0.000045 1.000000]]\n");
    double sdm_test[2] = {10.00,20.00};
    double **support_degree_test;
    support_degree_test = support_degree_matrix(SDM_TEST_ARRAY_SIZE,sdm_test);
    printf("OutPut 2-D array with below values\n");
    for(int i = 0; i < SDM_TEST_ARRAY_SIZE ; i ++){
        for(int j =0; j < SDM_TEST_ARRAY_SIZE ; j++){
            printf("{%d} - {%d} element value is %2f\n",i,j,support_degree_test[i][j]);
        }
    }
    free(support_degree_test);
    printf("*****************************************************\n");

    
    /*Testing of Function compute_integrated_support using 2* 1-D 
     * array alpha and principal_component
     * @input : alpha of size 2 [10 20] , principal_component of size 2 [1 2], size of array
     * @output expected : 1D array [10 40]
     */
    printf("Testing compute_integrated_support function using array alpha [10 20] and principal_component [1 2]\n");
    printf("Expected array is [10.00 40.00]\n");
    double alpha[2] = {10.00,20.00};
    double principal_component[2] = {1.00,2.00};
    double * integrated_support_op;
    integrated_support_op = compute_integrated_support(alpha,principal_component,INTEGRATED_SUPPORT_TEST_ARRAY_SIZE);
    printf("OutPut 1-D array with below values\n");
    for (int i = 0; i < INTEGRATED_SUPPORT_TEST_ARRAY_SIZE; i++){
        printf("%2f\n",integrated_support_op[i]);
    }
    free(integrated_support_op);

    printf("*****************************************************\n");
    /*Testing of Function elimination of integrated support using integrated support
     * here the return array contains value of integrated array except the value
     * which is below than 0.7*average value, those element will be 0
     * @input : integrated support [10 11 12 1] , size of array
     * @output expected : 1D array [10 11 12 0]
     */
    printf("Testing compute_integrated_support function using array integrated support [10 11 12 1]\n");
    printf("Expected array is [10.00 11.00 12.00 0.00]\n");
    double integrated_support[4] = {10.00,11.00,12.00,1.00};
    double * elimination_test_op;
    elimination_test_op = elimination_of_integrated_support(integrated_support,ELIMINATION_TEST_ARRAY_SIZE);
    printf("OutPut 1-D array with below values\n");
    for (int i = 0; i < ELIMINATION_TEST_ARRAY_SIZE; i++){
        printf("%2f\n",elimination_test_op[i]);
    }
    free(elimination_test_op);
    printf("*****************************************************\n");

    /*Testing of Function weight_coefficient using elimination matrix
     * returns the weight ( value / sum of array)
     * @input : elimination 1-D array [10 11 12 0] , size of array
     * @output expected : 1D array [10 11 12 0]
     */
    printf("Testing weight_coefficient function using array integrated support [10 11 12 0]\n");
    printf("Expected output [0.30 0.33 0.36 0.00]\n");
    double elimination_array[4] = {10.00,11.00,12.00,0.00};
    double * weights_test_op;
    weights_test_op = find_weight_coefficient(elimination_array,WEIGHT_TEST_ARRAY_SIZE);
    printf("OutPut 1-D array with below values\n");
    for (int i = 0; i < WEIGHT_TEST_ARRAY_SIZE; i++){
        printf("%2f\n",weights_test_op[i]);
    }
    free(weights_test_op);
    printf("*****************************************************\n");

    /*Testing of Function fused_output using sensor readings and weights 
     * this function produces final output which is estimated value of sensor fusion algorithm
     * @input : sensor readings [10 11 12 0], weights [0.27 0.25 0.28 0], size of readings
     * @output expected : 1D array [10 11 12 0]
     */
    printf("Testing weight_coefficient function using sensor readings [10 11 12 0],weights [0.27 0.25 0.28 0]\n");
    printf("Expected output 8.81\n");
    double sensor_readings[4] = {10.00,11.00,12.00,0.00};
    double weights[4]= {0.27,0.25,0.28,0};
    double fused_value;
    fused_value = fused_output(sensor_readings,weights,FUSED_OP_TEST_ARRAY_SIZE);
    printf("Fused value is %.2f\n",fused_value);
    printf("*****************************************************\n");
    return 0;
}