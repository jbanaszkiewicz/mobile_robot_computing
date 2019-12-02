#include "graph.h"
#include <iostream>

realT Node::getPositionX()const
{
  return this->position.first;
}

realT Node::getPositionY()const
{
  return this->position.second;
}

Graph::Graph(sizeT n_nodes)
{
  nodes = std::vector<Node>();
  nodes.reserve(n_nodes);
}

Graph::~Graph()
{
}

const std::vector<Node>& Graph::getNodes()const
{
  return nodes;
}

void Graph::addNode(std::pair<realT, realT>p)
{
  nodes.push_back(Node(p));   
}

void Graph::addEdge(const Node & from, const Node & to, realT distance)
{
  edges.insert( std::pair<keyT,valueT>(&from, valueT(&to, distance))); 
}

std::pair<mapT::const_iterator,mapT::const_iterator>
  Graph::getNeighbours(const Node* node)const
{
  return edges.equal_range( node);
}

void Graph::showGraph()const
{
  showNodes();
  showEdges();
}

void Graph::showNodes()const
{
  for(const auto& i : nodes)
  {
    std::cout << i.position.first << "," << i.position.second << std::endl;
  }
}

void Graph::showEdges()const
{
  for(const auto& i : edges)
  {
    std::cout << i.first->position.first <<","<< i.first->position.second << \
    "->" << i.second.first->position.first <<","<< i.second.first->position.first << std::endl;
  }
}
