#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

typedef struct sensor_data_s{
    float time;
    char name[10];
    double value;
} sensor_data_t;

void save_sensor_description(char* token, int token_count, sensor_data_t* sensor_description);

void print_sensor_description(sensor_data_t* sensor_description);

