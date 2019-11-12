#include "graph.h"
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
  edges[std::pair<Node,Node>(from,to)] = distance; 
  edges[std::pair<Node,Node>(to,from)] = distance; 
}