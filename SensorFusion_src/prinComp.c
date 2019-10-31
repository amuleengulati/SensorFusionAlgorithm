//import gsl files for matrix multiplication

double* Principal(double sdm[][], double lambda[], int n){
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
	    	y[i] = T[i][j] * lambda[i];
		}
	}
	return y;
}