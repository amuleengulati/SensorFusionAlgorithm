/* This file contains code to implement vector multiplication operation */
#include "multiply.h"

double multiply(double* eigen_vector, double* eigen_value){
int n = 4;
double sum = 0.0;

double* matrix;
matrix = (double*) malloc(n*sizeof(double));

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

/* Assign the matrix multipliction result to a matrix */
for (int i = 0; i < n; i++){
        matrix[i] = gsl_vector_get(v1, i);
        sum += matrix[i];
}
return sum;
}