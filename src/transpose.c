/* This file contains code to compute the transpose of a given matrix */
#include "transpose.h"

double** transpose(double** matrix, int n){
/* Create a matrix to store the transpose and allocate memory to it */ 
double** matrix_t;
matrix_t = (double**) malloc(n*sizeof(double));
for(int r = 0;r < n; r++){
    matrix_t[r] = (double*) malloc(n*sizeof(double));
}

/* Create a GSL matrix */
gsl_matrix* m = gsl_matrix_alloc(n,n);

/* Assign sample values to matrix */
for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
        gsl_matrix_set(m, i, j, matrix[i][j]);
}
}

/* Call the GSL transpose function */
gsl_matrix_transpose(m);

/* Assign the GSL transpose matrix to the created matrix */
for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
        matrix_t[i][j] = gsl_matrix_get(m, i, j);
}
}

/* return the transpose */
return matrix_t;
}
