#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int main()
{
double x[4] = {2.0,4.0,3.75,3.55};
double **D;
D = (double**) malloc(4*sizeof(double));
for(int r=0;r<4;r++)
{
D[4] = (double*) malloc(4*sizeof(double));
}
for(int i=0;i<4;i++)
{
for(int j=0;j<4;j++)
{
double diff = x[i]-x[j];
D[i][j] = exp(-diff);
printf("%f \n", D[i][j]);
}
}
return 0;
}