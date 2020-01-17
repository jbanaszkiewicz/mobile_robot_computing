#include "randomPath.h"
#include "path.h"
#include "graph.h"
#include "graphGenerator.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <exception>
#include <omp.h>
#include "iostream"
RandomPath::RandomPath(/* args */)
{}

RandomPath::~RandomPath()
{}

bool compareNeighbours(const Node& node1,const Node& node2, const Node& destination)
{
  return (GraphGenerator::normSquered(node1, destination) < GraphGenerator::normSquered(node2, destination));
}

/*
  Ta funkcja jest zrównoleglona ponieważ każdy proces generuje swój zestaw ścieżek.
  Zadbajmy o różne pseudo losowe ścieżki dla każdego procesu.
*/
std::vector<Path> RandomPath::getRandomPaths(
  const Graph & graph, sizeT numberOfPaths,const Node& start,const Node& destination)
{
  std::vector<Path> randomPaths = std::vector<Path>(numberOfPaths);
  srand(time(NULL));
  #pragma omp parallel for
  for(int i =0;i < numberOfPaths;++i)
  {
    Path currentPath = Path();
    const Node* currentNode = &start;
    
    
    /* Sprawdzam, czy w wektorze mam tyle losowych ścieżek, ile jest wymagane.
      Jeśli nie, rozpoczynam tworzenie nowej losowej ścieżki, którą dodam do wektora. */
    currentPath.addNodeToPath(&start);
    
    while (currentNode != &destination)
    {
      size_t indexOfChosenNeighbour = 0;
      std::vector<const Node*> neighbourNodes = graph.getNeighboursVector(graph.getNeighbours(currentNode));
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
        throw std::invalid_argument("Graph with no node around start node.");
      } else if (neighbourNodes.size() == 1)
      {
        indexOfChosenNeighbour=0;
      } else
      {
        int halfOfNeighbours = (neighbourNodes.size() / 2);
        indexOfChosenNeighbour = rand()%(halfOfNeighbours);

      }
      
      // Teraz muszę wylosować liczbę z zakresu od 0 do (halfOfNeighbours - 1)

      
      // Ustawienie nowego aktualnego węzła i dodanie go do aktualnej ścieżki
      currentNode = neighbourNodes[indexOfChosenNeighbour];
      currentPath.addNodeToPath(currentNode);
    }
    
    randomPaths[i] = currentPath;
  }
  return randomPaths;
}