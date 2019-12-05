/* This file contains code to implement matrix multiplication operation */

#include<stdio.h>
#include ".\gsl\gsl_matrix.h"
int main()
{
int n = 4;
double** matrix;
matrix = (double**) malloc(n*sizeof(double));
for(int r = 0;r < n;r++){
    matrix[r] = (double*) malloc(n*sizeof(double));
}

/* Create two GSL matrices */
gsl_matrix* m1 = gsl_matrix_alloc(n,n);
gsl_matrix* m2 = gsl_matrix_alloc(n,n);

/*Assign sample values to matrices */
for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
        gsl_matrix_set(m1, i, j, i*j);
}
}

for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
        gsl_matrix_set(m2, i, j, i+j);
}
}

/* Call GSL matrix multiplication function */
gsl_matrix_mul_elements(m1,m2);

/* Assign the matrix multipliction result to a matrix */
for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
        matrix[i][j] = gsl_matrix_get(m1, i, j);
}
}

/* Print the result */
for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
        printf("%f ",matrix[i][j]);
}
    printf("\n");
}
return 0;
}