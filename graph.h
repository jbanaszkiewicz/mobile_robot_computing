#ifndef GRAPH_H
#define GRAPH_H
#include <stddef.h>
#include <vector>
#include <utility>  /* pair */
#include <map>

using sizeT = size_t;
using realT = double;

class Node
{
public:
  std::pair<realT, realT> position;
  Node(std::pair<realT, realT> p)
  {
    position = p;
  }
};

class Graph
{
private:
  std::vector<Node> nodes;
  std::map<std::pair<Node&,Node&>,realT> edges;
  
public:
  Graph(sizeT n_nodes);
  ~Graph();
  std::vector<Node> getNodes();
  void addNode(std::pair<realT, realT>p);
  void addEdge(const Node & from, const Node & to,realT distance);
/* TODO  FUNKCJA wyswietlajaca graf zeby byl ten sam */
};

Graph::Graph(sizeT n_nodes)
{
  nodes = std::vector<Node>(n_nodes);
}

Graph::~Graph()
{
}


#endif //GRAPH_H