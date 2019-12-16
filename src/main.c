/** 
 * @file main.c
 * @author Amuleen Gulati
 * @date 15 Dec 2019
 * @brief Processing of input file, calling different functions to compute output and storing data in output file.
 *
 * Input file is a .csv containing sensor data. The program will output a single fused 
 * output value for seperate time values as well as a list of sensors which are out of
 * range. 
 */


#include<stdio.h>

/* Include all dependencies */
#include "..\include\sdm.h"
#include "..\include\eigen.h"
#include "..\include\principle_comp.h"
#include "..\include\contribution.h"
#include "..\include\parse.h"

#define DELIMITER ","
#define MAX_ENTRIES 100
#define MAX_LINE_SIZE 128

/* Declare a global variable to store the number of entries in an input file */
int total_entries = 0;

/**
 * \fn void save_sensor_description(char *token, int token_count, sensor_data_t* sensor_description[])
 * \brief
 * @param[in] token a single element from the current line (row) of the input .csv file.
 * @param[in] token_count an integer value to determine which entry (column) is being read.
 * @param[in] sensor_description an object of struct data type containing all fields for sensor data.
 *
 * @brief The function is used to assign sensor data read from the input file to a list.
 */
void save_sensor_description(char* token, int token_count, sensor_data_t* sensor_description){
    switch(token_count){
        case 1:
            sensor_description->time = strtof(token, NULL);
            break;
        case 2:
            strcpy(sensor_description->name, token);
            break;
        case 3:
            sensor_description->value = strtof(token, NULL);
            break;
        default:
            printf(" ERROR: Too much information for sensor, Ignoring extra data!\n");
            break;
    }
}

/**
 * \fn void print_sensor_description(sensor_data_t* sensor_description)
 * \brief
 * @param[in] sensor_description a pointer to the sensor whose value is to be printed.
 
 * @brief The function is used to print the sensor data read from the input .csv file.
 */
void print_sensor_description(sensor_data_t* sensor_description){
    printf("BEGINNING TO READ SENSOR DATA\n");
    printf("TIME: %f\nNAME: %s\nVALUE: %f\n", sensor_description->time, sensor_description->name, sensor_description->value);
}

/**
 * \fn void check(char* line, sensor_data_t* sensor_description)
 * \brief
 * @param[in] line a pointer to the current line of input which is being read.
 * @param[in] sensor_description a pointer to the structure object which will store the data on the line being read.
 
 * @brief The function is used to check whether the data being read has all the necessary fields.
 */
void check(char* line, sensor_data_t* sensor_description){
    int token_count = 1;
    while(token_count < 4){
        char* token = strtok(line, DELIMITER);
        while (token != NULL) { 
            save_sensor_description(token, token_count, sensor_description);
            token = strtok(NULL, DELIMITER); 
            token_count++;
        } 
    }
    if(token_count >= 4){
        printf("ERROR: TOO MUCH DATA! IGNORING EXTRA DATA!!\n");
    }
    else if(token_count < 3){
        printf("ERROR: INSUFFICIENT DATA! SKIPPING THIS ENTRY!!\n");
    }
}

/**
 * \fn void delete(int* array, int index)
 * \brief
 * @param[in] array a pointer to the array on which deletion has to be performed.
 * @param[in] index the position in the array where the element has to be deleted.
 
 * @brief The function is used to delete an array element in the required position.
 */
void delete(int* array, int index){
    for(int k = index; k < total_entries - 1; k++){
        array[k] = array[k + 1];
    }
total_entries--;
}

int main(){
    /* Declare a variable to hold the number of entries for a particular time */
    int n = 0;

    /* Open a file stream */
    FILE* input_file = fopen("..\\data\\input.csv", "rt");
    if(input_file == NULL){
        printf("File could not be opened: %s\n",strerror(errno));
        return 1;
    }
    else{
    printf("File opened successfully!\n");
    }

    char line[MAX_LINE_SIZE];
    sensor_data_t* sensor_description = (sensor_data_t*) malloc(sizeof(sensor_data_t));
    sensor_data_t sensor_description_list[100];

    /* Ignore the first line containing headers */
    fgets(line, sizeof(line), input_file);

    /* Parse the input .csv file to store the sensor data in variables */
    while((fgets(line,sizeof(line),input_file) != NULL)){
        check(line, &sensor_description_list[total_entries++]);
    }

    /**
    * Declare 2 arrays to manage input processing. 
    * temp_array store the indices which have not been processed yet.
    * input_array stores the sensor values for a particular time of input.
    */
    int temp_array[total_entries];
    double input_array[total_entries];

    /* Fill the temp_array with indices for input processing. */
    for(int i = 0; i < total_entries; i++){
        temp_array[i] = i;
    }

    /**
    * Call the functions to compute fused output seperately for different time values.
    * In each iteration, fused output for one time value is computed.
    * temp_array is updated in each iteration to store only those indices which have not been processed yet.
    * The loop continues until all sensor entries are processed.
    */
    while(total_entries){
        for(int j = 1; j < total_entries; j++){
            int entry = 0;
            if(sensor_description_list[temp_array[0]].time == sensor_description_list[temp_array[j]].time){
                input_array[entry] = sensor_description_list[temp_array[j]].value;
                entry = entry + 1;
                delete(temp_array,j);
            }
            input_array[entry] = sensor_description_list[temp_array[0]].value;
            float time = sensor_description_list[temp_array[0]].time;
            entry = entry + 1;
            delete(temp_array, 0);
            for(int k = 0; k < entry; k++){
                printf("\nINPUT ARRAY %f", input_array[k]);
                n = k + 1;
            }

            /* Declare a 2-D matrix to store the SDM matrix. */  
            double** sd_matrix;
            sd_matrix = (double**) malloc(n*sizeof(double));
            for(int r = 0; r < n; r++){
                sd_matrix[r] = (double*) malloc(n*sizeof(double));
            }
            sd_matrix = support_degree_matrix(n,input_array);

            /* Declare a 2-D matrix to store eigen vectors. */
            double** T;
            T = (double**) malloc(n*sizeof(double));
            for(int r = 0; r < n; r++){
                T[r] = (double*) malloc(n*sizeof(double));
            }
            T = eigen_vector(n, sd_matrix);

            /* Declare a vector to store eigen values. */
            double* D;
            D = (double*) malloc(n*sizeof(double));
            D = eigen_value(n, sd_matrix);

            /* Declare a vector to store principle component values. */
            double* prin_comp;
            prin_comp = (double*) malloc(n*sizeof(double));
            prin_comp = principle_component(n, T, D);

            /* Declare a vector to store the contribution values of first m principle components. */
            double* contribution_m;
            contribution_m = (double*) malloc(n*sizeof(double));
            contribution_m = contribution(n, D);
            for(int i = 0; i < n; i++){
            printf("\nTIME: %2f CONTRIBUTION: %f ",time, contribution_m[i]);}
        }
    }

    /* Close the input file */
    fclose(input_file);
    return 0;
}