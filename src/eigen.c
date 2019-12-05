/*This file contains code to compute the eigen values and eigen vectors of the support degree matrix. It takes an nXn matrix and computes its eigen values and eigen vectors using GSL library functions.*/

#include <stdio.h>
#include ".\gsl\eigen\gsl_eigen.h"
#include ".\gsl\gsl_math.h"

int main(int argc, char ** argv){
int n = 2;

/*Initialize an nXn matrix to store eigen vectors */ 
double **evector;
evector = (double**) malloc(n*sizeof(double));
for(int r = 0;r < n;r++){
    evector[r] = (double*) malloc(n*sizeof(double));
}

/*Initialize an array to store eigen values */
double* evalue;
evalue = (double*) malloc(n*sizeof(double));

/* Create a GSL matrix M */
gsl_matrix* M = gsl_matrix_alloc(n, n);

/* Fill the matrix with values */
gsl_matrix_set(M, 0, 0, 3);
gsl_matrix_set(M, 0, 1, 2);
gsl_matrix_set(M, 1, 0, 3);
gsl_matrix_set(M, 1, 1, -2);

/* Assign the elements of Matrix
for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
        gsl_matrix_set(M, i, j, matrix_values);
}
}*/

/* Create a GSL vector to store eigenvalues */
gsl_matrix* evecs = gsl_matrix_alloc(n,n);

/* Create a GSL vector to store eigenvalues */
gsl_vector* evals = gsl_vector_alloc(n);

/* Initialize an eigen workspace */
gsl_eigen_symmv_workspace* workspace = gsl_eigen_symmv_alloc(n);

/* Compute the eigenvalues and eigenvectors */
gsl_eigen_symmv(M, evals, evecs, workspace);

/*Assign the computed eigenvectors to the evector matrix */
for (int i = 0; i < n; i++){
    for(int j = 0;j < n;j++){
	evector[i][j] = gsl_matrix_get(evecs, i, j);
}
}

/*Assign the computed eigenvalues to the evalues vector */
for (int i = 0; i < n; i++){
    evalue[i] = gsl_vector_get(evals, i);
}

/* Free the GSL memory */
gsl_eigen_symmv_free(workspace);
gsl_matrix_free(M);
gsl_matrix_free(evecs);
gsl_vector_free(evals);

return    0;
}