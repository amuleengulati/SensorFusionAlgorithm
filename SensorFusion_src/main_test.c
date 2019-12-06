/*******************************************************
* Author : Shyam Bhuptani 
* Function : Unit Testing of all Functions
*/

/*Including all dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include "../include/Support_Degree_Matrix.h"
#include "../include/contribution.h"
#define num1 2
#define num2 3

// Main test function
int main(int argc, char ** argv){

    /*Testing of Function Support Degree Matrix using one-D array*/
    printf("*****************************************************\n");
    printf("Testing Support degree function using array [10,20]\n");
    int sdm_test[2] = {10,20};
    double **Support_Degree_TEST;
    Support_Degree_TEST = Support_Degree_Matrix(num1,sdm_test);
    printf("OutPut 2-D array with below values\n");
    for(int i = 0; i < num1 ; i ++){
        for(int j =0; j < num1 ; j++){
            printf("{%d} - {%d} element value is %2f\n",i,j,Support_Degree_TEST[i][j]);
        }
    }
    free(Support_Degree_TEST);
    printf("*****************************************************\n");
    /*Testing of Function Contribution using one-D array*/
    printf("Testing Contribution function using array [23,34,45]\n");
    double contri_test[3] = {23,34,45};
    double * contri_test_op;
    contri_test_op = Contribution(num2,contri_test);
    printf("OutPut 1-D array with below values\n");
    for (int i = 0; i < num2; i++){
        printf("%2f\n",contri_test_op[i]);
    }
    free(contri_test_op);
    printf("*****************************************************\n");
    return 0;
}