#include "..\include\parse.h"

#define DELIMITER ","

int total_entries = 0;
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

void print_sensor_description(sensor_data_t* sensor_description){
    printf("BEGINNING TO READ SENSOR DATA\n");
    printf("TIME: %f\nNAME: %s\nVALUE: %f\n", sensor_description->time, sensor_description->name, sensor_description->value);
}

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
}

void delete(int* array, int index){
    for(int k = index; k < total_entries - 1; k++){
        array[k] = array[k + 1];
    }
total_entries--;
}
int main(int argc, char* argv[])
{

/*if(argc != 2){
printf("Usage: You need to invoke the program with your file name in .csv format\n");
}*/

FILE* input_file = fopen("..\\data\\input.csv", "rt");
if(input_file == NULL){
    printf("File could not be opened: %s\n",strerror(errno));
    return 1;
}
else{
    printf("File opened successfully!\n");
}


char line[128];

sensor_data_t* sensor_description = (sensor_data_t*) malloc(sizeof(sensor_data_t));
sensor_data_t sensor_description_list[100];

fgets(line, sizeof(line), input_file);

while((fgets(line,sizeof(line),input_file) != NULL)){
        check(line, &sensor_description_list[total_entries++]);
}
    /*print_sensor_description(sensor_description);
    printf("DONE READING!\n");*/

    int temp_array[total_entries];
    double input_array[total_entries];
    int entry = 0;

    for(int i = 0; i < total_entries; i++){
        temp_array[i] = i;
    }
        for(int j = 1; j < total_entries; j++){
            if(sensor_description_list[temp_array[0]].time == sensor_description_list[temp_array[j]].time){
                input_array[entry] = sensor_description_list[temp_array[j]].value;
                entry = entry + 1;
                delete(temp_array,j);
            }
            input_array[entry] = sensor_description_list[temp_array[0]].value;
            entry = entry + 1;
            delete(temp_array, 0);
            
       }
    
fclose(input_file);
return 0;
}