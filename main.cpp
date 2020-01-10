#include "psoTests.h"
#include "graphGenerator.h"
#include "psoPathSearch.h"
#include <chrono>
#include <cstdlib>
#include <iostream>
#include "mpi.h"

using namespace std::chrono;

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int nr_of_particles = 2; 
  // std::cin >> nr_of_particles;
  int nr_of_iterators = 2;
  // std::cin >> nr_of_iterators;

  bool inputFromFile = true;
  // std::cin >> inputFromFile;

  auto graph = Graph(0);
  if (!inputFromFile){
    double radiusOfNeighbourhood = 2;
    int graphNrOfNodes = 4;
    // std::cin >> graphNrOfNodes;
    // std::cin >> radiusOfNeighbourhood;
    graph = GraphGenerator::getGraph(graphNrOfNodes, radiusOfNeighbourhood);
    graph.saveToFile("./graphs/graph2", radiusOfNeighbourhood);
  }
  else{
    std::string graphPath   = "./graphs/graph1000";
    // std::cin >> graphPath;
    graph = Graph::getGraph(graphPath);
  }

  graph.showGraph();

  
  auto search = PsoPathSearch(graph,GraphGenerator::getStart(graph),GraphGenerator::getDestination(graph));

  auto start = high_resolution_clock::now();   //COMPLETED: KUBA poczatek czasu
  std::pair<Path,costT> bestSolution = search.FindShortestPath(nr_of_particles, nr_of_iterators);
  Path best_path = bestSolution.first;
  costT cost_best_path = bestSolution.second;

  auto stop = high_resolution_clock::now(); //COMPLETED: KUBA koniec czasu
  
  auto duration = duration_cast<microseconds>(stop - start).count();  //COMPLETED: KUBA policz duration
  
  std::cout<<duration<<std::endl<< cost_best_path<<std::endl; // koszt sciezki
  MPI_Finalize();
  return 0;
}