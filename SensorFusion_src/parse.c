/*******************************************************************************************/
/* Author : Shyam Bhuptani 
/* Function : Parse 
/* Application : This function converts the input csv file into a sensor reading1-D array
/* this parse file is for tag 1 which only works fine for one time value
/* here the number of sensor is fixed which is 3
/* Input : csv file of data  with 3 fields Time(24hr clock) , sensor_name, value
/* Output : sensor reading array of size N (double)
*/

/*Including dependancies*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>	

#include "../include/parse.h"	 
//Number of sensors are fixed
#define num_of_sensor 3

/*Function declaration which returns a 2D array */
double *Parse(char file_name[])
{
	printf("file name is %s\n",file_name);
    int iterations = 0;
    double *sensor_readings = (double *) malloc(num_of_sensor * sizeof(double *));
	printf("here1");
    FILE* stream = fopen(file_name,"r");
	printf("here2");
	/*If stream is not present*/
    if (!stream){
        printf("Can't Open file");
    }
    char line[1024];
	printf("here");
    while(fgets(line,1024,stream)){
        /*Using below condition removing the headers as the first row of
		input file is assumed to be headers*/
		printf("line is %s\n",line);
		if(iterations == 0){
            iterations++;
            continue;
        }
        else{
            int count = 0;
			/*Defining local variables*/
            float time,sensor_value;
            char * sensor_name;
			/*delimiter will be comma as input is csv*/
            char * delimiter = strtok(line,",");
            while(delimiter){
                if(count == 0){
					/*First element of row is time
					atof is used to convert time into a float*/
                    time = (float)(atof(delimiter));
                }
                if(count == 1){
					/*Second element of row is sensor_name*/
                    sensor_name = delimiter;
                }
                if(count == 2){
					/*last element of row is value
					using atof we are converting string into float*/
                    sensor_value = (float)(atof(delimiter));
				}
                delimiter = strtok(NULL,",");
                count++;
            }
			/*Sensor name conversion into output array's index*/
            strcpy(sensor_name, sensor_name + 4);
            int number = atoi(sensor_name);
            sensor_readings[number] = sensor_value;
        }
        iterations++;
    }
    return sensor_readings;
}