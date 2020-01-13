#include "psoTests.h"
#include "graphGenerator.h"
#include "psoPathSearch.h"
#include <chrono>
#include <cstdlib>
#include <iostream>


using namespace std::chrono;
// TODO Kuba dokończyć konfigurację c++ wg https://code.visualstudio.com/docs/cpp/config-mingw 
int main(int argc, char **argv) {
  // PsoTests::runTests();

  if (argc<=1){   //COMPLETED get argv 
    std::cout<<"You haven't passed required arguments to the program."<<std::endl;

    return 0;
  }
  float radiusOfNeighbourhood;
  bool inputFromFile = atoi(argv[1]);
  int nr_of_particles     = atoi(argv[2]);
  int nr_of_iterators     = atoi(argv[3]);
  int nr_of_threads;
  auto graph = Graph(0);
  if(argc >=5)  nr_of_threads = atoi(argv[4]);
  else          nr_of_threads = 1;
  // omp_set_num_threads(nr_of_threads);
  if (!inputFromFile){
    int graphNrOfNodes = atoi(argv[5]);
    double radiusOfNeighbourhood = atof(argv[6]);
    graph = GraphGenerator::getGraph(graphNrOfNodes, radiusOfNeighbourhood);
    // auto duration = duration_cast<microseconds>(stop - start).count()
    graph.saveToFile("./graphs/graph2", radiusOfNeighbourhood);
  }
  else{
    graph = Graph::getGraph(argv[5]);
  }
  
    
  
  auto search = PsoPathSearch(graph,GraphGenerator::getStart(graph),GraphGenerator::getDestination(graph));

  auto start = high_resolution_clock::now();   //COMPLETED: KUBA poczatek czasu
  std::pair<Path,costT> bestSolution = search.FindShortestPath(nr_of_particles, nr_of_iterators);
  Path best_path = bestSolution.first;
  costT cost_best_path = bestSolution.second;

  auto stop = high_resolution_clock::now(); //COMPLETED: KUBA koniec czasu
  
  auto duration = duration_cast<microseconds>(stop - start).count();  //COMPLETED: KUBA policz duration
  
  std::cout<<duration<<std::endl<< cost_best_path<<std::endl; // koszt sciezki

  //TODO: statystyki
    // czas wyszukiwania search.findshortestpath
    //ilosc nodów koncowej
    //dlugosc sciezki konsowej
    //wielkosc grafu -> ktory z zapisanych do pliku
    //nr_of_particles, nr_of_iterations
  
  // nazwa grafu 
  // całkowity czas 
  // liczba wątków 

  //TODO: sprawdzic po ilu interacjach generowania sciezka wynikowa jest zawsze taka sama i tą ilość iteracji wybrać jako końcową  -> zadanie na pozniej
  //TODO: KUBA zrobić make projektu
  return 0;
}