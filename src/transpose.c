/* This file contains code to compute the transpose of a given matrix */

#include<stdio.h>
#include ".\gsl\gsl_matrix.h"

int main()
{
int n = 4;

/* Create a matrix to store the transpose and allocate memory to it */ 
double** matrix;
matrix = (double**) malloc(n*sizeof(double));
for(int r = 0;r < n; r++){
    matrix[r] = (double*) malloc(n*sizeof(double));
}

/* Create a GSL matrix */
gsl_matrix* m = gsl_matrix_alloc(n,n);

/* Assign sample values to matrix */
for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
        gsl_matrix_set(m, i, j, i+j);
}
}

/* Call the GSL transpose function */
gsl_matrix_transpose(m);

/* Assign the GSL transpose matrix to the created matrix */
for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
        matrix[i][j] = gsl_matrix_get(m, i, j);
}
}

/* Print the transpose */
for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
        printf("%f ",matrix[i][j]);
}
    printf("\n");
}
return 0;
}