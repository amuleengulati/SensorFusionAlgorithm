double* contribution(double lambda[], int n)
{
	double sum = 0.0;
	
	//compute summation of all eigen values
	for(int i=0;i<n;i++){
		sum += lambda[i];
	}		
	
	//compute contribution rate for each component 
	for(int i=0;i<n;i++){
		alpha[i] = lambda[i]/sum;
	}
//the function returns an 1Xn vector alpha[n] containing the contribution rate of each component
return alpha;
}