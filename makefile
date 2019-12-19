#MAKEFILE
CC=gcc
INC_DIR = include
CFLAGS=-O0 -std=c11 -I $(INC_DIR)
GSL= gsl-config --cflags --libs

#CREATE BIN, BUILD, AND RESULTS FOLDERS TO SAVE THE COMPILED FILES DURING RUNTIME
bin_folder := $(shell mkdir -p bin)
build_folder := $(shell mkdir -p build)

#TARGET TO BUILD EVERYTHING
sdm.o: src/sdm.c
	$(CC) -g -c $(CFLAGS) src/sdm.c -o build/sdm.o

eigen_value.o: src/eigen_value.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` src/eigen_value.c -o build/eigen_value.o

eigen_vector.o: src/eigen_vector.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` src/eigen_vector.c -o build/eigen_vector.o

multiply.o: src/multiply.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` src/multiply.c -o build/multiply.o

transpose.o: src/transpose.c
	$(CC) -g -c $(CFLAGS) src/transpose.c `$(GSL)` -o build/transpose.o

principle_comp.o: src/principle_comp.c
	$(CC) -g -c $(CFLAGS) src/principle_comp.c `$(GSL)` -o build/principle_comp.o

contribution_k.o: src/contribution_k.c
	$(CC) -g -c $(CFLAGS) src/contribution_k.c -o build/contribution_k.o

contribution.o: src/contribution.c
	$(CC) -g -c $(CFLAGS) src/contribution.c -o build/contribution.o

integrated_support.o: src/integrated_support.c
	$(CC) -g -c $(CFLAGS) src/integrated_support.c -o build/integrated_support.o

weight_coefficient.o: src/weight_coefficient.c
	$(CC) -g -c $(CFLAGS) src/weight_coefficient.c -o build/weight_coefficient.o

elimination.o: src/elimination.c
	$(CC) -g -c $(CFLAGS) src/elimination.c -o build/elimination.o

fused_output.o: src/fused_output.c
	$(CC) -g -c $(CFLAGS) src/fused_output.c -o build/fused_output.o

auto_unit_test.o: src/test/auto_unit_test.c
	$(CC) -g -c $(CFLAGS)`$(GSL)` src/test/auto_unit_test.c -o build/auto_unit_test.o

main.o: src/main.c
	$(CC) -g -c $(CFLAGS) `$(GSL)` src/main.c -o build/main.o
	
#TARGET TO COMPILE EVERYTHING 
main: main.o sdm.o contribution.o contribution_k.o multiply.o eigen_value.o eigen_vector.o sdm.o transpose.o integrated_support.o elimination.o weight_coefficient.o fused_output.o principle_comp.o 
		$(CC) -g -o bin/main build/main.o build/sdm.o build/contribution.o build/eigen_value.o build/eigen_vector.o build/transpose.o build/contribution_k.o build/multiply.o build/integrated_support.o build/elimination.o build/weight_coefficient.o build/fused_output.o build/principle_comp.o `$(GSL)`

test: auto_unit_test.o sdm.o contribution.o contribution_k.o multiply.o eigen_value.o eigen_vector.o sdm.o transpose.o integrated_support.o elimination.o weight_coefficient.o fused_output.o principle_comp.o 
		$(CC) -g -o bin/test build/auto_unit_test.o build/sdm.o build/contribution.o build/eigen_value.o build/eigen_vector.o build/transpose.o build/contribution_k.o build/multiply.o build/integrated_support.o build/elimination.o build/weight_coefficient.o build/fused_output.o build/principle_comp.o `$(GSL)`

all: main test

#CLEAN COMMANDS
clean: 
	rm -f bin/* build/*