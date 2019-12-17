#MAKEFILE
CC=gcc
INC_DIR = include
CFLAGS=-O0 -std=c11 -I $(INC_DIR)

#CREATE BIN, BUILD, AND RESULTS FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p result)

#TARGET TO BUILD EVERYTHING
contribution.o: SensorFusion_src/contribution.c
	$(CC) -g -c $(CFLAGS) SensorFusion_src/contribution.c -o build/contribution.o

contribution_m.o: SensorFusion_src/contribution_m.c
	$(CC) -g -c $(CFLAGS) SensorFusion_src/contribution_m.c -o build/contribution_m.o

	
file_io.o: src/file_io.c
	$(CC) -g -c $(CFLAGS) src/file_io.c -o build/file_io.o

sensor_fusion.o: src/sensor_fusion.c
	$(CC) -g -c $(CFLAGS) src/sensor_fusion.c -o build/sensor_fusion.o
	





#TARGET TO COMPILE EVERYTHING 
all: main.o file_io.o sensor_fusion.o
		$(CC) -g -o bin/SensorFusion build/main.o build/file_io.o build/sensor_fusion.o

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*