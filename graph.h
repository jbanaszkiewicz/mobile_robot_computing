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
using keyT = std::pair<const Node&,const Node&>;

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
};

class Graph
{
private:
  std::vector<Node> nodes;
  std::map<keyT,realT> edges;
  
public:
  Graph(sizeT n_nodes);
  ~Graph();
  std::vector<Node> getNodes();
  void addNode(std::pair<realT, realT>p);
  void addEdge(const Node & from, const Node & to,realT distance);
  realT getPathLength(const Path & path)const;

/* TODO  FUNKCJA wyswietlajaca graf zeby byl ten sam */
};

#endif //GRAPH_H