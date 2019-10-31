double* weight_coefficient(double Z'[])
{
	int n = sizeof(Z');
	int sum = 0;
	for(int i = 0;i<n;i++)
		sum+=Z'[i];
	for(int i = 0;i<n;i++)
		w[i] = Z'[i]/sum;
	
return w;
}