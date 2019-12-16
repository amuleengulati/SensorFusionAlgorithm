/******************************************************
* Author : Amuleen Gulati 
* Function : contribution
* Application : This function computes the compute the 
* contribution rate of m principal components 
* Input : number of sensors n as integer, eigen value vector D[n]   
* Output : vector of size n of contributions of m principle components
*/

#include "..\include\contribution.h"

double* contribution(int n, double* D){

/*Compute the sum of eigen_value vector */
double sum = 0.0;
for(int i=0;i<n;i++){
    sum += D[i];
}

/*Compute the contribution rate of kth principal component*/
double* alpha;
alpha = (double*) malloc(n*sizeof(double));
for(int k=0;k<n;k++){
    alpha[k] = D[k]/sum;
}

/* Compute the contribution rate of m principal components */
double* psi;
psi = (double*) malloc(n*sizeof(double));
psi[0] = alpha[0];
for(int m=1;m<n;m++){
    psi[m] = psi[m-1] + alpha[m];
}
return psi;
}