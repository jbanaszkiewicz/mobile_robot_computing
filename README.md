# mobile_robot_computing
The project tests parallel and distributed computing. We implement them on Particle Swarm Optimization. The algorithm is used to choose optimum path.

## Budowanie programu
```sh
g++  -g -fopenmp graphGenerator.cpp graph.cpp path.cpp psoPathSearch.cpp psoTests.cpp randomPath.cpp main.cpp
```