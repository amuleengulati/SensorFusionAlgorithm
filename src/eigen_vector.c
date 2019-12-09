/******************************************************
* Author : Amuleen Gulati
* Function : eigen vector 
* Application : This function computes the eigen vectors matrix having degree  
* n*n for the input sd_matrix[n][n] (the SDM matrix) 
* Input : size of SDM matrix n as integer and sd_matrix[n][n] of doubles 
* Output : n*n matrix of eigen vectors
*/

#include "..\include\eigen.h"

double** eigen_vector(int n, double** D){

/*Initialize an nXn matrix to store eigen vectors */ 
double **evector;
evector = (double**) malloc(n*sizeof(double));
for(int r = 0;r < n;r++){
    evector[r] = (double*) malloc(n*sizeof(double));
}

/* Create a GSL matrix M */
gsl_matrix* M = gsl_matrix_alloc(n, n);

/* Assign the elements of Matrix */
for (int i = 0; i < n; i++){
    for (int j = 0; j < n; j++){
        gsl_matrix_set(M, i, j, D[i][j]);
    }
}

/* Create a GSL matrix to store eigenvectors */
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

/* Free the GSL memory
gsl_eigen_symmv_free(workspace);
gsl_matrix_free(M);
gsl_matrix_free(evecs);
gsl_vector_free(evals); */

return evector;
}