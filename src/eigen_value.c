/******************************************************
* Author : Amuleen Gulati
* Function : eigen value
* Application : This function computes the eigen values vector having degree n for 
* an input matrix[n][n] (the SDM matrix)
* Input : number of sensors n as integer and sd_matrix[n][n] of doubles 
* Output : vector of size n of eigen vectors
*/

#include "..\include\eigen.h"

double* eigen_value(int n, double** D){
/*Initialize an array to store eigen values */
double* evalue;
evalue = (double*) malloc(n*sizeof(double));

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

/*Assign the computed eigenvalues to the evalues vector */
for (int i = 0; i < n; i++){
    evalue[i] = gsl_vector_get(evals, i);
}
return evalue;
}