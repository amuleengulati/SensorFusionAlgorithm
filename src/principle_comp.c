#include<stdio.h>
#include ".\gsl\gsl_matrix.h"
#include "transpose.h"
#include "multiply.h"

int main()
{
int n = 4;

/* Taking a sample eigen_value vector*/
double eigen_value[4] = {2,3,4,5};

/* Create a vector to store principal component values */
double* y;
y = (double*) malloc(n*sizeof(double));

/*Create a vector to store individual eigen vectors*/
double* eigen_vector;
eigen_vector = (double*) malloc(n*sizeof(double));

/*Create a matrix to store the values */
double** matrix;
matrix = (double**) malloc(n*sizeof(double));
for(int r = 0;r < n;r++){
    matrix[r] = (double*) malloc(n*sizeof(double));
}

/* Create a GSL matrix */
gsl_matrix* m = gsl_matrix_alloc(n,n);

/* Assign sample values to GSL matrix and fill the matrix*/
for(int i = 0;i < n;i++){
    for(int j = 0;j < n;j++){
        gsl_matrix_set(m, i, j, i+j);
        matrix[i][j] = gsl_matrix_get(m, i, j);
}
}

/* Call transpose function */
matrix = transpose(matrix, 4);

/*Modify GSL matrix to contain transposed values */ 
for(int i = 0;i < n;i++){
    for(int j = 0;j < n;j++){
        gsl_matrix_set(m, i, j, matrix[i][j]);
}
}

/* Create vertical splits of matrix to access individual eigen vectors */
for(int i=0;i<n;i++){
    gsl_vector_view v = gsl_matrix_column(m,i);
    for(int j=0;j<n;j++){
        eigen_vector[j] = gsl_vector_get(&v.vector,j);
}
    y[i] = multiply(eigen_vector, eigen_value);
}
return 0;
}
