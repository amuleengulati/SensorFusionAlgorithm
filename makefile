#MAKEFILE
CC=gcc
INC_DIR = include
CFLAGS=-O0 -std=c11 -I $(INC_DIR)
GSL= gsl-config --cflags --libs

#CREATE BIN, BUILD, AND RESULTS FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)
results_folder := $(shell mkdir -p result)


#TARGET TO BUILD EVERYTHING
contribution.o: SensorFusion_src/contribution.c
	$(CC) -g -c $(CFLAGS) SensorFusion_src/contribution.c -o build/contribution.o

contribution_m.o: SensorFusion_src/contribution_m.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` SensorFusion_src/contribution_m.c -o build/contribution_m.o

eigenValue.o: SensorFusion_src/eigenValue.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` SensorFusion_src/eigenValue.c -o build/eigenValue.o

eigenVector.o: SensorFusion_src/eigenVector.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` SensorFusion_src/eigenVector.c -o build/eigenVector.o

elimination.o: SensorFusion_src/elimination.c
	$(CC) -g -c $(CFLAGS) SensorFusion_src/elimination.c -o build/elimination.o

fused_output.o: SensorFusion_src/fused_output.c
	$(CC) -g -c $(CFLAGS) SensorFusion_src/fused_output.c -o build/fused_output.o

integrated_support.o: SensorFusion_src/integrated_support.c
	$(CC) -g -c $(CFLAGS) SensorFusion_src/integrated_support.c -o build/integrated_support.o
	
support_degree_matrix.o: SensorFusion_src/support_degree_matrix.c
	$(CC) -g -c $(CFLAGS) SensorFusion_src/support_degree_matrix.c -o build/support_degree_matrix.o
	
transpose.o: SensorFusion_src/transpose.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` SensorFusion_src/transpose.c -o build/transpose.o
	
weight_coefficient.o: SensorFusion_src/weight_coefficient.c
	$(CC) -g -c $(CFLAGS) SensorFusion_src/weight_coefficient.c -o build/weight_coefficient.o

main_test.o: test/SensorFusion_test_src/main_test.c
	$(CC) -g -c $(CFLAGS) test/SensorFusion_test_src/main_test.c -o build/main_test.o

main.o: SensorFusion_src/main.c
	$(CC) -g -c $(CFLAGS) SensorFusion_src/main.c -o build/main.o
	
#TARGET TO COMPILE EVERYTHING 
main: main.o support_degree_matrix.o contribution.o integrated_support.o elimination.o weight_coefficient.o fused_output.o
		$(CC) -g -o bin/main build/main.o build/support_degree_matrix.o build/contribution.o build/integrated_support.o build/elimination.o build/weight_coefficient.o build/fused_output.o

test: main_test.o support_degree_matrix.o contribution.o integrated_support.o elimination.o weight_coefficient.o fused_output.o
		$(CC) -g -o bin/main_test build/main_test.o build/support_degree_matrix.o build/contribution.o build/integrated_support.o build/elimination.o build/weight_coefficient.o build/fused_output.o

all: test
#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*