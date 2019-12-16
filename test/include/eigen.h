#ifndef __EIGEN_H__
#define __EIGEN_H__

#include "..\lib\gsl\eigen\gsl_eigen.h"
#include "..\lib\gsl\gsl_math.h"

double** eigen_vector(int n, double** D);
double* eigen_value(int n,double** D);

#endif