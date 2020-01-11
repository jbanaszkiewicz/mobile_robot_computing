#include "psoTests.h"
#include "graphGenerator.h"
#include "psoPathSearch.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <mpi.h>

using namespace std::chrono;

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  if (argc<=1){   //https://stackoverflow.com/questions/9185792/passing-arguments-via-command-line-with-mpi
    std::cout<<"You haven't passed required arguments to the program."<<std::endl;

    return 0;
  }
  float radiusOfNeighbourhood;
  bool inputFromFile = atoi(argv[1]);
  int nr_of_particles     = atoi(argv[2]);
  int nr_of_iterators     = atoi(argv[3]);
  auto graph = Graph(0);

  if (!inputFromFile){
    int graphNrOfNodes = atoi(argv[4]);
    double radiusOfNeighbourhood = atof(argv[5]);
    graph = GraphGenerator::getGraph(graphNrOfNodes, radiusOfNeighbourhood);
    // auto duration = duration_cast<microseconds>(stop - start).count()
    graph.saveToFile("./graphs/graph2", radiusOfNeighbourhood);
  }
  else{
    graph = Graph::getGraph(argv[4]);
  }
  
  // liczba cząsteczek na proces
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  nr_of_particles = nr_of_particles/world_size;
  
  auto search = PsoPathSearch(graph,GraphGenerator::getStart(graph),GraphGenerator::getDestination(graph));
  // bariera przed pomiarem czasu
  // procesy rozpoczynają pracę w tym samym momencie
  // bez względu na czas wczytania pliku
  MPI_Barrier(MPI_COMM_WORLD);
  auto start = high_resolution_clock::now();   //COMPLETED: KUBA poczatek czasu
  solutionT bestSolution = search.FindShortestPath(nr_of_particles, nr_of_iterators);
  Path best_path = bestSolution.first;
  costT cost_best_path = bestSolution.second;
  auto stop = high_resolution_clock::now(); //COMPLETED: KUBA koniec czasu
  
  auto duration = duration_cast<microseconds>(stop - start).count();  //COMPLETED: KUBA policz duration
  
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  if(world_rank == 0)
  {
    std::cout<<duration<<std::endl<< cost_best_path<<std::endl; // koszt sciezki
  }

  MPI_Finalize();
  return 0;
}