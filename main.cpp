#include "psoTests.h"

int main(int argc, char **argv) {
  PsoTests::runTests();
  //todo napisac funkcje zapisujaca graf do pliku ADAM
    // trzeba zapisac do pliku tylko wspolrzedne wezlow. Warunek tworzenia wezla to max odleglosc . implementacja to wczytanie nodow zamiast ich losowania
  //todo napisac funckje wczytujaca plik z grafem do grafu ADAM
  //todo dodac pliki zrodlowe tutaj
  
  auto graph = GraphGenerator::getGraph(3, 2.0);
  auto search = PsoPathSearch(graph,GraphGenerator::getStart(graph),GraphGenerator::getDestination(graph));
  //todo poczatek czasu KUBA
  //path, path_cost =  search.findshortestpath(nr_of_particles, nr_of_iterations) //todo jakas tak funkcja
  //todo koniec czasu KUBA
  //todo policz duration KUBA

  //todo wygenerowac plik wielokrotnie uruchamiajacy skrypt KUBA
    //przekazac przez argv rozmiar grafu, nr_of_particles, nr_of_iterations-> do findshortestpath

  //todo statystyki
    // czas wyszukiwania search.findshortestpath
    //ilosc nodów koncowej
    //dlugosc sciezki konsowej
    //wielkosc grafu -> ktory z zapisanych do pliku
    //nr_of_particles, nr_of_iterations
  

  //todo sprawdzic po ilu interacjach generowania sciezka wynikowa jest zawsze taka sama i tą ilość iteracji wybrać jako końcową  -> zadanie na pozniej
  // zrobić make projektu ADAM KUBA
  //dodac .vs do git ignore KUBA
}