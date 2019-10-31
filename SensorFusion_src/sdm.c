#include<math.h>

double** SDM(float x[], int n){

  //declaring the SDM matrix
  double *sdm[n][n];

  //assigning memory to SDM matrix
  for(int i=0;i<n;i++){
    sdm[i] = (double*)malloc(n*sizeof(double));
}

  //filling up the SDM matrix
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      double diff = x[i] - x[j];
      sdm[i][j] = exp(-diff);
}
}

//returns an nXn matrix
return sdm;
}