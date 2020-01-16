INC=-I/usr/local/cuda/include
NVCC=nvcc
NVCC_OPT=-std=c++11
DEPS=graph.cpp graphGenerator.cpp graphGPU.cpp main.cpp path.cpp pathGPU.cpp psoPathSearch.cpp psoPathSearchGPU.cpp psoTests.cpp randomPath.cpp

all:
	$(NVCC) $(NVCC_OPT) -x cu $(DEPS) 

# clean :
# 	rm main $(OBJ) 
# -g  #flag for gdb
#-Wall -Wextra -pedantic  
