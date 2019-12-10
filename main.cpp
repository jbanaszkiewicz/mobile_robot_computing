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
  int graphNrOfNodes = atoi(argv[1]);
  int nr_of_particles     = atoi(argv[2]);
  int nr_of_iterators     = atoi(argv[3]);

  // TODO: CO TO? Warunek tworzenia wezla to max odleglosc . implementacja to wczytanie nodow zamiast ich losowania
  
  auto graph = GraphGenerator::getGraph(graphNrOfNodes, 2.0);
  graph.saveToFile("./graphs/graph1");

  // auto search = PsoPathSearch(graph,GraphGenerator::getStart(graph),GraphGenerator::getDestination(graph));

  // auto start = high_resolution_clock::now();   //COMPLETED: KUBA poczatek czasu
  // std::pair<Path,costT> bestSolution = search.FindShortestPath(nr_of_particles, nr_of_iterators);
  // Path best_path = bestSolution.first;
  // costT cost_best_path = bestSolution.second;

  // auto stop = high_resolution_clock::now(); //COMPLETED: KUBA koniec czasu
  
  // auto duration = duration_cast<microseconds>(stop - start).count();  //COMPLETED: KUBA policz duration
  
  // std::cout<<duration<<std::endl<<cost_best_path<<std::endl;
  //TODO: statystyki
    // czas wyszukiwania search.findshortestpath
    //ilosc nodów koncowej
    //dlugosc sciezki konsowej
    //wielkosc grafu -> ktory z zapisanych do pliku
    //nr_of_particles, nr_of_iterations
  

  //TODO: sprawdzic po ilu interacjach generowania sciezka wynikowa jest zawsze taka sama i tą ilość iteracji wybrać jako końcową  -> zadanie na pozniej
  //TODO: KUBA zrobić make projektu
  return 0;
}