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
  realT getPositionX()const;
  realT getPositionY()const;
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
  void showGraph()const;
  void showEdges()const;
  void showNodes()const;


  friend class PsoTests;
};

#endif //GRAPH_H