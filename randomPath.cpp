#include "randomPath.h"
#include "path.h"
#include "graph.h"
#include "graphGenerator.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <exception>
RandomPath::RandomPath(/* args */)
{}

RandomPath::~RandomPath()
{}

bool compareNeighbours(const Node& node1,const Node& node2, const Node& destination)
{
  return (GraphGenerator::normSquered(node1, destination) < GraphGenerator::normSquered(node2, destination));
}

std::vector<Path> RandomPath::getRandomPaths(
  const Graph & graph, sizeT numberOfPaths,const Node& start,const Node& destination)
{
  //TODO: KUBA zrownoleglic generowanie losowych sciezek KUBA
  std::vector<Path> randomPaths;
  std::vector<const Node*> neighbourNodes;
  Path *currentPath;
  const Node* currentNode = &start;
  int halfOfNeighbours = 0;
  size_t indexOfChosenNeighbour = 0;
  srand(time(NULL));
  
  //TODO: ALL dopilnować zarządzania oryginałami i kopiami węzłów
  while (randomPaths.size() < numberOfPaths)
  {
    /* Sprawdzam, czy w wektorze mam tyle losowych ścieżek, ile jest wymagane.
      Jeśli nie, rozpoczynam tworzenie nowej losowej ścieżki, którą dodam do wektora. */
    currentPath = new Path();
    currentPath->addNodeToPath(&start);
    
    while (currentNode != &destination)
    {
      neighbourNodes = graph.getNeighboursVector(graph.getNeighbours(currentNode));
      // Sytuacja wygląda tak: funkcja getNeighbours zwraca parę iteratorów
      // A chyba miało być tak, że w jakiś sposób dowiaduję się o wszystkich sąsiadach
      // I to z nich wybieram lepszą połowę

      // Zakładam, że w tym miejscu mam już kilka node'ów sąsiednich, z których mam wylosować
      // Sortowanie elementów w wektorze sąsiadów ze względu na kwadrat ich odległości od destination
      std::sort(neighbourNodes.begin(), neighbourNodes.end(), 
        [&](const Node* node1, const Node* node2 )->bool
        {
          return compareNeighbours(*node1, *node2, destination);
        });

      // Ustalam liczbę odpowiadającą połowie sąsiadów
      if (neighbourNodes.size() == 0)
      {
        halfOfNeighbours = 0;
        throw std::invalid_argument("Graph with no node around start node.");
      } else if (neighbourNodes.size() == 1)
      {
        halfOfNeighbours = 1;
        indexOfChosenNeighbour=0;
      } else
      {
        halfOfNeighbours = (neighbourNodes.size() / 2);
        indexOfChosenNeighbour = rand()%(halfOfNeighbours);

      }
      
      // Teraz muszę wylosować liczbę z zakresu od 0 do (halfOfNeighbours - 1)

      
      // Ustawienie nowego aktualnego węzła i dodanie go do aktualnej ścieżki
      currentNode = (neighbourNodes.at(indexOfChosenNeighbour));
      currentPath->addNodeToPath(currentNode);
    }
    
    randomPaths.push_back(*currentPath);
  }

  return randomPaths;
}