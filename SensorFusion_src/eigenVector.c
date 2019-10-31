#include<<gsl/gsl_matrix.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>

double** eigenVector(double sdm[][], int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)
		{
			//compute eigen vectors
			//compute T[i][j]
			//compute transpose of T[i][j] after each iteration of i & store it in T
		}
	}
//returns an nXn vector containing the eigen vectors
return T;
}