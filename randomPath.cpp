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
  
  //TODO: ADAM dopisać generator ścieżek
  //while vector size < NumberofPaths: losuj dalej sciezke:
    //while currentNode != destination:
      
      //z sasiednich node'ow wybierz loswy
      // sprawdz czy jest on Node estination
        //jezeli nie jest 
          // //z polowy najlepszych nodow sasiednich wybierz nastepnego (getNeighbours) 
          //(jakosc oceniana na podstawie kwadratu odl do destination x y (graffenerator.NormSquared))
          //dodaj do obecnej sciezki

        //jezeli jest dodaj sciezke do vectora sciezek

      //zwróć vector ściezek


      
          


  // throw std::logic_error("getRandomPaths Not Implemented");
  return std::vector<Path>();
}