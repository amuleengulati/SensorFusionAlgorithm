/*******************************************************
* Author : Shyam Bhuptani 
* Function : Unit Testing of all Functions
*/

/*Including all dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include "../include/support_degree_matrix.h"
#include "../include/contribution.h"
#define sdm_test_array_size 2
#define contribution_test_array_size 3

// Main test function
int main(int argc, char ** argv){

    /*Testing of Function Support Degree Matrix using one-D input array
    * This function performs (e^-(abolute(reading[i]-reading[j]))) for 2 sensors 
    * and provides results
    * @input : double array of size 2 for testing with value [10.00, 20.00]
    * @output expected : 2D array [[1.000000 0.000045] [0.000045 1.000000]]
    */
    printf("*****************************************************\n");
    printf("Testing Support degree function using array [10.00,20.00]\n");
    double sdm_test[2] = {10.00,20.00};
    double **support_degree_test;
    support_degree_test = build_support_degree_matrix(sdm_test,sdm_test_array_size);
    printf("OutPut 2-D array with below values\n");
    for(int i = 0; i < sdm_test_array_size ; i ++){
        for(int j =0; j < sdm_test_array_size ; j++){
            printf("{%d} - {%d} element value is %2f\n",i,j,support_degree_test[i][j]);
        }
    }
    free(support_degree_test);
    printf("*****************************************************\n");
    /*Testing of Function compute_contributions using one-D input array
    * @input : double array of size 3 for testing with value [23 34 45]
    * @output expected : 2D array [0.225490 0.333333 0.441176]
    */
    printf("Testing compute_contributions function using array [23.00,34.00,45.00]\n");
    double contri_test[3] = {23.00,34.00,45.00};
    double * contri_test_op;
    contri_test_op = compute_contributions(contri_test,contribution_test_array_size);
    printf("OutPut 1-D array with below values\n");
    for (int i = 0; i < contribution_test_array_size; i++){
        printf("%2f\n",contri_test_op[i]);
    }
    free(contri_test_op);
    printf("*****************************************************\n");
    return 0;
}