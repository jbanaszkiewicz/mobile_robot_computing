#include "psoTests.h"

int main(int argc, char **argv) {
  PsoTests::runTests();
  //TODO: ADAM napisac funkcje zapisujaca graf do pliku
    // trzeba zapisac do pliku tylko wspolrzedne wezlow. Warunek tworzenia wezla to max odleglosc . implementacja to wczytanie nodow zamiast ich losowania
  //TODO: ADAM napisac funckje wczytujaca plik z grafem do grafu
  //TODO: ADAM dodac pliki zrodlowe tutaj
  
  auto graph = GraphGenerator::getGraph(3, 2.0);
  auto search = PsoPathSearch(graph,GraphGenerator::getStart(graph),GraphGenerator::getDestination(graph));
  //TODO: KUBA poczatek czasu
  //path, path_cost =  search.findshortestpath(nr_of_particles, nr_of_iterations) //TODO: jakas tak funkcja
  //TODO: KUBA koniec czasu
  //TODO: KUBA policz duration

  //TODO: KUBA wygenerowac plik wielokrotnie uruchamiajacy skrypt
    //przekazac przez argv rozmiar grafu, nr_of_particles, nr_of_iterations-> do findshortestpath

  //TODO: statystyki
    // czas wyszukiwania search.findshortestpath
    //ilosc nodów koncowej
    //dlugosc sciezki konsowej
    //wielkosc grafu -> ktory z zapisanych do pliku
    //nr_of_particles, nr_of_iterations
  

  //TODO: sprawdzic po ilu interacjach generowania sciezka wynikowa jest zawsze taka sama i tą ilość iteracji wybrać jako końcową  -> zadanie na pozniej
  //TODO: ADAM KUBA zrobić make projektu
  //TODO: KUBA dodac .vs do git ignore
}