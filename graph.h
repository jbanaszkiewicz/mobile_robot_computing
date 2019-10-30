#ifndef GRAPH_H
#define GRAPH_H
#include <stddef.h>

using sizeT = size_t;
using realT = double;

class Graph
{
private:
  /* data */
public:
  Graph(sizeT nodes);
  ~Graph();
  void addEdge(sizeT from, sizeT to);
};

Graph::Graph(sizeT nodes)
{
}

Graph::~Graph()
{
}


#endif //GRAPH_H