/******************************************************
* Author : Amuleen Gulati 
* Function : multiply
* Application : This function computes the product of 
* two vectors
* Input : eigen vector matrix T[n][n], eigen value vector D[n]   
* Output : product of two vectors
*/

#include "..\include\multiply.h"

double multiply(double* eigen_vector, double* eigen_value){
int n = 4;
double sum = 0.0;

double* vector;
vector = (double*) malloc(n*sizeof(double));

/* Create two GSL vectors */
gsl_vector* v1 = gsl_vector_alloc(n);
gsl_vector* v2 = gsl_vector_alloc(n);

/*Assign values to vectors */
for (int i = 0; i < n; i++){
        gsl_vector_set(v1, i, eigen_vector[i]);
}

for (int i = 0; i < n; i++){
        gsl_vector_set(v2, i, eigen_value[i]);
}

/* Call GSL vector multiplication function */
gsl_vector_mul(v1,v2);

/* Assign the matrix multipliction result to a vector */
for (int i = 0; i < n; i++){
        vector[i] = gsl_vector_get(v1, i);
        sum += vector[i];
}
return sum;
}