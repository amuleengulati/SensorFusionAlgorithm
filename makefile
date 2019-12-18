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
contribution.o: src/contribution.c
	$(CC) -g -c $(CFLAGS) src/contribution.c -o build/contribution.o

contribution_k.o: src/contribution_k.c
	$(CC) -g -c $(CFLAGS) src/contribution_k.c -o build/contribution_k.o
	
multiply.o: src/multiply.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` src/multiply.c -o build/multiply.o

eigen_value.o: src/eigen_value.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` src/eigen_value.c -o build/eigen_value.o

eigen_vector.o: src/eigen_vector.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` src/eigen_vector.c -o build/eigen_vector.o

elimination.o: src/elimination.c
	$(CC) -g -c $(CFLAGS) src/elimination.c -o build/elimination.o

fused_output.o: src/fused_output.c
	$(CC) -g -c $(CFLAGS) src/fused_output.c -o build/fused_output.o

integrated_support.o: src/integrated_support.c
	$(CC) -g -c $(CFLAGS) src/integrated_support.c -o build/integrated_support.o
	
sdm.o: src/sdm.c
	$(CC) -g -c $(CFLAGS) src/sdm.c -o build/sdm.o
	
transpose.o: src/transpose.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` src/transpose.c -o build/transpose.o
	
weight_coefficient.o: src/weight_coefficient.c
	$(CC) -g -c $(CFLAGS) src/weight_coefficient.c -o build/weight_coefficient.o

auto_unit_test.o: src/test/src/auto_unit_test.c
	$(CC) -g -c $(CFLAGS)`$(GSL)` src/test/src/auto_unit_test.c -o build/auto_unit_test.o

main.o: src/main.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` src/main.c -o build/main.o
	
#TARGET TO COMPILE EVERYTHING 
main: main.o sdm.o contribution.o contribution_k.o multiply.o eigen_value.o eigen_vector.o sdm.o tranpose.o integrated_support.o elimination.o weight_coefficient.o fused_output.o
		$(CC) -g -o bin/main build/main.o build/sdm.o build/contribution.o build/eigen_value.o build/eigen_vector.o build/transpose.o build/contribution_k.o build/multiply.o build/integrated_support.o build/elimination.o build/weight_coefficient.o build/fused_output.o

test: auto_unit_test.o sdm.o contribution.o contribution_k.o multiply.o eigen_value.o eigen_vector.o sdm.o tranpose.o integrated_support.o elimination.o weight_coefficient.o fused_output.o
		$(CC) -g -o bin/test build/auto_unit_test.o build/sdm.o build/contribution.o build/eigen_value.o build/eigen_vector.o build/transpose.o build/contribution_k.o build/multiply.o build/integrated_support.o build/elimination.o build/weight_coefficient.o build/fused_output.o

all: main test

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*