/*******************************************************
* Author : Shyam Bhuptani 
* Function : Unit Testing of all Functions
*/

/*Including all dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include "../include/support_degree_matrix.h"
#include "../include/contribution.h"
#include "../include/integrated_support.h"
#include "../include/elimination.h"
#include "../include/weight_coefficient.h"
#include "../include/fused_output.h"
#include "../include/parse.h"

#define SDM_TEST_ARRAY_SIZE 2
#define CONTRIBUTION_TEST_ARRAY_SIZE 3
#define INTEGRATED_SUPPORT_TEST_ARRAY_SIZE 2
#define ELIMINATION_TEST_ARRAY_SIZE 4
#define WEIGHT_TEST_ARRAY_SIZE 4
#define FUSED_OP_TEST_ARRAY_SIZE 4
#define NUMBER_OF_SENSOR 3

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
	printf("Expected array is [[1.000000 0.000045] [0.000045 1.000000]]\n");
    double sdm_test[2] = {10.00,20.00};
    double **support_degree_test;
    support_degree_test = build_support_degree_matrix(sdm_test,SDM_TEST_ARRAY_SIZE);
    printf("OutPut 2-D array with below values\n");
    for(int i = 0; i < SDM_TEST_ARRAY_SIZE ; i ++){
        for(int j =0; j < SDM_TEST_ARRAY_SIZE ; j++){
            printf("{%d} - {%d} element value is %2f\n",i,j,support_degree_test[i][j]);
        }
    }
    free(support_degree_test);
    printf("*****************************************************\n");
    /*Testing of Function compute_contributions using one-D input array
    * @input : double array of size 3 for testing with value [23 34 45],size of array
    * @output expected : 2D array [0.225490 0.333333 0.441176]
    */
    printf("Testing compute_contributions function using array [23.00,34.00,45.00]\n");
	printf("Expected array is [0.225490 0.333333 0.441176]\n");
    double contri_test[3] = {23.00,34.00,45.00};
    double * contri_test_op;
    contri_test_op = compute_contributions(contri_test,CONTRIBUTION_TEST_ARRAY_SIZE);
    printf("OutPut 1-D array with below values\n");
    for (int i = 0; i < CONTRIBUTION_TEST_ARRAY_SIZE; i++){
        printf("%2f\n",contri_test_op[i]);
    }
    free(contri_test_op);
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
    printf("Fused value is %2f\n",fused_value);
	printf("*****************************************************\n");
	/*Testing of parse using input csv file
	* this function produces an array and length of array will be equal to total number of sensor
	* and the elements will be respective value for sensors
    * @input : sample input_data.csv
    * @output expected : 1D array with all sensor values
    */
    printf("Testing of input_data.csv file\n");
	printf("Expected output [45 46 50]\n");
    char file_name[] = "..\\data\\input.csv";
    double *sensor_value = (double *) malloc(NUMBER_OF_SENSOR * sizeof(double *));
    sensor_value = parse(file_name);
    for(int i = 0; i < NUMBER_OF_SENSOR; i++){
        printf("%2f\n",sensor_value[i]);
    }
    return 0;
	printf("*****************************************************\n");
	
	
    return 0;
}