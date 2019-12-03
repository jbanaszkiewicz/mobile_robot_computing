#include "graph.h"
#include <iostream>
#include <fstream>

realT Node::getPositionX()const
{
  return this->position.first;
}

realT Node::getPositionY()const
{
  return this->position.second;
}

void Node::setPositionX(realT x)
{
  this->position.first = x;
}

void Node::setPositionY(realT y)
{
  this->position.second = y;
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

void Graph::saveToFile(std::string filename)const
{
  std::ofstream outputFile;
  realT currentX, currentY;
  outputFile.open(filename);

  for (size_t i = 0; i < this->nodes.size(); i++)
  {
    currentX = this->nodes.at(i).getPositionX();
    currentY = this->nodes.at(i).getPositionY();
    outputFile << currentX << '\n' << currentY << '\n';
  }
  
  outputFile.close();
}

std::vector<Node> Graph::getNodesFromFile(std::string filename)const
{
  std::vector<Node> nodesFromFile;
  std::pair<realT, realT> currentPosition;
  std::ifstream inputFile;

  inputFile.open(filename);

  while (! inputFile.eof())
  {
    inputFile >> currentPosition.first;
    inputFile >> currentPosition.second;
    nodesFromFile.push_back(Node(currentPosition));
  }

  inputFile.close();

  // TODO: ADAM Przerobić funkcję na voida

  return nodesFromFile;
}
