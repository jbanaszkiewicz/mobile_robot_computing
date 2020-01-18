#ifndef GRAPH_H
#define GRAPH_H
#include <stddef.h> // size_t
#include <vector>
#include <utility>  /* pair */
#include <map>

class Node;
class Path;

using sizeT = size_t;
using realT = double;
using keyT = const Node*;
using valueT = std::pair<const Node*,realT>;
using mapT = std::multimap<keyT,valueT>;

// Klasa reprezentująca pojedynczy węzeł grafu
class Node
{
public:
  // Pozycja węzła
  std::pair<realT, realT> position;

  // Konstruktor
  Node(std::pair<realT, realT> p)
  :position(p)
  {}

  // Operatory pozwalające na porównywanie dwóch węzłów
  bool operator<(const Node& right)const
  {
    return this->position < right.position;
  }
  bool operator==(const Node* right)
  {
    return this->position == right->position;
  }
  bool operator!=(const Node* right)
  {
    return this->position != right->position;
  }
  
  // Gettery i settery dotyczące położenia węzła w przestrzeni
  realT getPositionX()const;
  realT getPositionY()const;
  void setPositionX(realT x);
  void setPositionY(realT y);
};

// Klasa reprezentująca graf
class Graph
{
private:
  // węzły grafu
  std::vector<Node> nodes;
  // brzegi grafu łączące węzły
  mapT edges;
  
public:
  // Konstruktor grafu
  Graph(sizeT n_nodes);
  // Destruktor grafu
  ~Graph();
  // Getter pobierający węzły grafu
  const std::vector<Node>& getNodes()const;
  // Funkcja dodająca węzeł do grafu
  void addNode(std::pair<realT, realT>p);
  // Funkcja dodająca brzeg pomiędzy dwa węzły grafu
  void addEdge(const Node& from, const Node& to,realT distance);
  // Funkcja pozwalająca na ustalenie "sąsiadów" węzła grafu
  std::pair<mapT::const_iterator,mapT::const_iterator>
    getNeighbours(const Node* node)const;
  // Funkcja zwracająca vector "sąsiadów" węzła grafu
  std::vector<const Node*> getNeighboursVector(
    std::pair<mapT::const_iterator,mapT::const_iterator> neighbours
  )const;
  // Funkcja pokazująca graf
  void showGraph()const;
  // Funkcja pokazująca brzegi
  void showEdges()const;
  // Funkcja pokazująca węzły
  void showNodes()const;
  // Funkcja zapisująca graf do pliku
  void saveToFile(std::string filename, realT radiusOfNeighbourhood)const;
  // Funkcja wczytująca węzły z pliku
  std::vector<Node> getNodesFromFile(std::string filename)const;

  friend class PsoTests;
  // Funkcja pobierająca graf z pliku
  static Graph getGraph(std::string filename);
};

#endif //GRAPH_H