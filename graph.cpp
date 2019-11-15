#include "graph.h"
Graph::Graph(sizeT n_nodes)
{
  nodes = std::vector<Node>();
}

Graph::~Graph()
{
}

std::vector<Node> Graph::getNodes()
{
  return nodes;
}

void Graph::addNode(std::pair<realT, realT>p)
{
  nodes.push_back(Node(p));   
}
void Graph::addEdge(const Node & from, const Node & to, realT distance)
{
  edges[keyT(from,to)] = distance; 
  edges[keyT(to,from)] = distance; 
}

realT Graph::getPathLength(const Path & path)const
{
  throw std::logic_error("getPathLength Not Implemented");
  return realT();
}