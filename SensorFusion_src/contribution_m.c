double*  contribution_m(double alpha[], int n)
{
//we can construct a recursive function to compute the value of psi

//the function will compute a 1Xn vector psi[n], containing the contribution rates of m principle components	

//set the value of p to 0.75 initially; we can tune this parameter later to get the best one.
int count = 0;
for(int i = 0; i < n;i++)
{
	if(psi[i] > p)
		count++;
	else
		//delete psi[i] from the psi[n] vector
}
//the function returns a 1Xm vector containing contribution rates of m principle components
return psi;
}