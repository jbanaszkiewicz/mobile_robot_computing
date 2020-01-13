INC=-I/usr/local/cuda/include
NVCC=/usr/local/cuda/bin/nvcc
NVCC_OPT=-std=c++11
DEPS =  graphGenerator.h graph.h path.h psoPathSearch.h psoTests.h randomPath.h
OBJ = main.o graphGenerator.o graph.o path.o psoPathSearch.o psoTests.o randomPath.o

%.o: %.c $(DEPS)
	$(CC) -g -c -o  $@ $< $(CFLAGS)

psoMain: $(OBJ) 
	$(CC) -g -o main $(OBJ) $(CFLAGS)

clean :
	rm main $(OBJ) 
# -g  #flag for gdb
#-Wall -Wextra -pedantic  
