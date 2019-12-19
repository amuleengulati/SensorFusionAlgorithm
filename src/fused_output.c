<<<<<<< HEAD
/***********************************************************************
* Author : Shyam Bhuptani 
* Function : fused_output
* Application : This function produces the final output by simply adding 
* all the multiplication of input array(x) with their respective weights
* Input : sensor_readings(n),weights(n),number of sensors
* Output : derived_value
*/
=======
/**
 *
 * \fn fused_output(double sensor_readings[], double weights[], int n)
 * \author Shyam Bhuptani
 * \brief TThis function produces the final output by simply adding 
 * all the multiplication of input array(x) with their respective weights
 * Input : sensor_readings(n),weights(n),number of sensors
 * @param[in] sensor_readings(n)
 * @param[in] weights(n)
 * @param[in] number of sensors
 * @return derived_value
 */
>>>>>>> b02659bc402c93ac15c7ff8712f0198ba60bedb9

/*Including dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include "../include/fused_output.h"


double fused_output(double sensor_readings[], double weights[], int n){
    double fused_value = 0;
    /*Fused value is summation of all respective readings*weights */ 
    for(int i = 0; i < n; i++){ 
        fused_value += sensor_readings[i] * weights[i];
    }
    return fused_value;
}