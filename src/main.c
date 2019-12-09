/******************************************************
* Author : Amuleen Gulati 
* Function : main
* Application : This function takes sensor values as input and 
* calls different functions to produce an output
* Input : a .csv file containing temperature values of sensors
* Output : a single temperature value
*/

#include<stdio.h>

#include "..\include\sdm.h"
#include "..\include\eigen.h"
#include "..\include\principle_comp.h"
#include "..\include\contribution.h"

int main()
{
int n = 4;
double temperature[] = {2.75,3.55,3.70,4.0};

double** sd_matrix;
sd_matrix = (double**) malloc(n*sizeof(double));
for(int r = 0; r < n; r++){
    sd_matrix[r] = (double*) malloc(n*sizeof(double));
}
sd_matrix = support_degree_matrix(n,temperature);

double** T;
T = (double**) malloc(n*sizeof(double));
for(int r = 0; r < n; r++){
    T[r] = (double*) malloc(n*sizeof(double));
}
T = eigen_vector(n, sd_matrix);

double* D;
D = (double*) malloc(n*sizeof(double));
D = eigen_value(n, sd_matrix);

double* prin_comp;
prin_comp = (double*) malloc(n*sizeof(double));
prin_comp = principle_component(n, T, D);

double* contribution_m;
contribution_m = (double*) malloc(n*sizeof(double));
contribution_m = contribution(n, D);

return 0;
}