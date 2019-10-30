CC=gcc
CFLAGS=-I. -fopenmp
DEPS = pso.h psoTests.h psoPrivate.h graph.h
OBJ = main.o pso.o psoTests.o graph.o


%.o: %.c $(DEPS)
	$(CC) -g -c -o  $@ $< $(CFLAGS)

psoMain: $(OBJ) 
	$(CC) -g -o main $(OBJ) $(CFLAGS)

clean :
	rm main $(OBJ) 
# -g  #flag for gdb
#-Wall -Wextra -pedantic 