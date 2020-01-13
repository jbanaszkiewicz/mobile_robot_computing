INC=-I/usr/local/cuda/include
NVCC=/usr/local/cuda/bin/nvcc
NVCC_OPT=-std=c++11
DEPS=  graphGenerator.cpp graph.cpp path.cpp psoPathSearch.cpp psoTests.cpp randomPath.cpp main.cpp

all:
	$(NVCC) $(NVCC_OPT) -x cu $(DEPS) 

# clean :
# 	rm main $(OBJ) 
# -g  #flag for gdb
#-Wall -Wextra -pedantic  
