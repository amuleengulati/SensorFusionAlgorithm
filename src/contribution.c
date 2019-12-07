/* This file contains code to compute the contribution rate of m principal components */

/* The function prototype for this function after combining all the files will be 
double* contribution(double* eigen_value, int n);
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int main()
{
int n=4;
/* Taking a sample eigen value vector */
double eigen_value[4] = {2,3,4,5};

/*Compute the sum of eigen_value vector */
double sum = 0.0;
for(int i=0;i<n;i++){
    sum += eigen_value[i];
}

/*Compute the contribution rate of kth principal component*/
double* alpha;
alpha = (double*) malloc(n*sizeof(double));
for(int k=0;k<n;k++){
    alpha[k] = eigen_value[k]/sum;
}

/* Compute the contribution rate of m principal components */
double* psi;
psi = (double*) malloc(n*sizeof(double));
psi[0] = alpha[0];
for(int m=1;m<n;m++){
    psi[m] = psi[m-1] + alpha[m];
}
return 0;
}