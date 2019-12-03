#include "randomPath.h"
#include "path.h"
#include "graph.h"

RandomPath::RandomPath(/* args */)
{}

RandomPath::~RandomPath()
{}

std::vector<Path> RandomPath::getRandomPaths(
  const Graph & graph, sizeT numberOfPaths,const Node& start,const Node& destination)
{
  //TODO: KUBA zrownoleglic generowanie losowych sciezek KUBA
  std::vector<Path> randomPaths;
  Path *currentPath;
  Node currentNode = start;
  
  //TODO: ADAM dopisać generator ścieżek
  while (randomPaths.size() < numberOfPaths)
  {
    /* Sprawdzam, czy w wektorze mam tyle losowych ścieżek, ile jest wymagane.
      Jeśli nie, rozpoczynam tworzenie nowej losowej ścieżki, którą dodam do wektora. */
    currentPath = new Path();
    
    while (currentNode != destination)
    {
      /* code */
    }
    
    // TODO: ADAM Sprawdź, czy ten zapis będzie działał poprawnie
    randomPaths.push_back(*currentPath);
  }
  
  //while vector size < NumberofPaths: losuj dalej sciezke:
    //while currentNode != destination:
      
      //z sasiednich node'ow wybierz loswy
      // sprawdz czy jest on Node destination
        //jezeli nie jest 
          // //z polowy najlepszych nodow sasiednich wybierz nastepnego (getNeighbours) 
          //(jakosc oceniana na podstawie kwadratu odl do destination x y (graffenerator.NormSquared))
          //dodaj do obecnej sciezki

        //jezeli jest dodaj sciezke do vectora sciezek

      //zwróć vector ściezek

  return randomPaths;
}