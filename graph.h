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
using valueT = std::pair<const Node*,realT>; // para (węzeł na którym kończy się krawędź, długość krawędzi)
using mapT = std::multimap<keyT,valueT>; // lista sąsiedztwa w formie multimapy par (węzeł z którego wychodzi krawędz, valueT)

class Node
{
public:
  std::pair<realT, realT> position;

  Node(std::pair<realT, realT> p)
  :position(p)
  {}

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
  // TODO: ADAM zapytaj chłopaków, czy porównanie może opierać się jedynie na współrzędnych, a nie na adresie

  realT getPositionX()const;
  realT getPositionY()const;
  void setPositionX(realT x);
  void setPositionY(realT y);
};

class Graph
{
private:
  std::vector<Node> nodes;
  mapT edges;
  
public:
  Graph(sizeT n_nodes);
  ~Graph();
  const std::vector<Node>& getNodes()const;
  void addNode(std::pair<realT, realT>p);
  void addEdge(const Node& from, const Node& to,realT distance);
  std::pair<mapT::const_iterator,mapT::const_iterator>
    getNeighbours(const Node* node)const;
  std::vector<const Node*> getNeighboursVector(
    std::pair<mapT::const_iterator,mapT::const_iterator> neighbours
  )const;
  void showGraph()const;
  void showEdges()const;
  void showNodes()const;
  void saveToFile(std::string filename, realT radiusOfNeighbourhood)const;
  std::vector<Node> getNodesFromFile(std::string filename)const;
  friend class PsoTests;
  static Graph getGraph(std::string filename);

  std::vector<sizeT> getNodeIndexesFromPath(const Path& path)const;
  Path getPathFromNodeIndexes(const std::vector<sizeT>& indexes)const;
  sizeT getNodeIndex(const Node * n)const;
};

#endif //GRAPH_H