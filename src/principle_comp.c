/******************************************************
* Author : Amuleen Gulati 
* Function : principle component 
* Application : This function computes the principle component values
* for the input eigen values and eigen vectors
* Input : number of sensors n as integer, eigen vector matrix T[n][n], eigen value vector D[n]   
* Output : vector of size n of principle components
*/

#include "..\include\principle_comp.h"
#include "..\include\transpose.h"
#include "..\include\multiply.h"

double* principle_component(int n, double** D, double* T){

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
        gsl_matrix_set(m, i, j, D[i][j]);
        matrix[i][j] = gsl_matrix_get(m, i, j);
}
}

/* Call transpose function */
matrix = transpose(matrix, n);

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
    y[i] = multiply(eigen_vector, T);
}
return y;
}
