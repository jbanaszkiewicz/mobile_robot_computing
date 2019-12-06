#include "psoTests.h"
#include "graphGenerator.h"
#include "psoPathSearch.h"
#include <chrono>
#include <cstdlib>

using namespace std::chrono;

int main(int argc, char **argv) {
  PsoTests::runTests();
  //TODO get argv 
  if (argc<1){
    printf("You haven't passed required arguments to the program.");

    return -1;
  }
  int graphNrOfNodes = atoi(argv[1]);
  int nr_of_particles     = atoi(argv[2]);
  int nr_of_iterators     = atoi(argv[3]);

    // TODO: CO TO? Warunek tworzenia wezla to max odleglosc . implementacja to wczytanie nodow zamiast ich losowania
  
  auto graph = GraphGenerator::getGraph(graphNrOfNodes, 2.0);
  auto search = PsoPathSearch(graph,GraphGenerator::getStart(graph),GraphGenerator::getDestination(graph));

  auto start = high_resolution_clock::now();   //COMPLETED: KUBA poczatek czasu
  std::pair<Path,costT> bestSolution = search.FindShortestPath(nr_of_particles, nr_of_iterators);
  Path best_path = bestSolution.first;
  costT cost_best_path = bestSolution.second;

  auto stop = high_resolution_clock::now(); //COMPLETED: KUBA koniec czasu
  
  auto duration = duration_cast<microseconds>(stop - start);  //COMPLETED: KUBA policz duration


  //TODO: statystyki
    // czas wyszukiwania search.findshortestpath
    //ilosc nodów koncowej
    //dlugosc sciezki konsowej
    //wielkosc grafu -> ktory z zapisanych do pliku
    //nr_of_particles, nr_of_iterations
  

  //TODO: sprawdzic po ilu interacjach generowania sciezka wynikowa jest zawsze taka sama i tą ilość iteracji wybrać jako końcową  -> zadanie na pozniej
  //TODO: KUBA zrobić make projektu
  //TODO: KUBA dodac .vs do git ignore
  return 0;
}