#include "graph.h"
#include <iostream>
#include <fstream>
#include "graphGenerator.h"
#include "path.h"

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

std::vector<const Node*> Graph::getNeighboursVector(
  std::pair<mapT::const_iterator,mapT::const_iterator> neighbours
)const
{
  std::vector<const Node*> neighboursVector;

  for (auto i = neighbours.first; i != neighbours.second; ++i)
  {
    neighboursVector.push_back((*i).second.first);
  }
  
  return neighboursVector;
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

void Graph::saveToFile(std::string filename, realT radiusOfNeighbourhood)const
{
  std::ofstream outputFile;
  realT currentX, currentY;
  sizeT graphSize = nodes.size();
  outputFile.open(filename);
  outputFile << graphSize << '\n'<<radiusOfNeighbourhood << '\n';
  for (size_t i = 0; i < this->nodes.size(); i++)
  {
    currentX = this->nodes.at(i).getPositionX();
    currentY = this->nodes.at(i).getPositionY();
    outputFile << currentX << '\n' << currentY << '\n';
  }
  
  outputFile.close();
}

Graph Graph::getGraph(std::string filename)
{
  std::vector<Node> nodesFromFile;
  std::pair<realT, realT> currentPosition;
  std::ifstream inputFile;
  realT radiusOfNeighbourhood;
  
  inputFile.open(filename);
  
  sizeT nrNodes; 
  inputFile >> nrNodes;
  Graph graph = Graph(nrNodes);
  inputFile >> radiusOfNeighbourhood; 
  while (! inputFile.eof())
  {
    inputFile >> currentPosition.first;
    inputFile >> currentPosition.second;
    graph.addNode(currentPosition);
  }
  inputFile.close();
  graph = GraphGenerator::addEdges(graph, radiusOfNeighbourhood);
  return graph;
}


std::vector<sizeT> Graph::getNodeIndexesFromPath(const Path& path)const
{
  auto indexes = std::vector<sizeT>();
  indexes.reserve(path.nodes.size());

  for(const auto n : path.nodes)
  {
    indexes.push_back(getNodeIndex(n));
  }

  return indexes;
}

sizeT Graph::getNodeIndex(const Node * n)const
{
  return n - nodes.data();
}

Path Graph::getPathFromNodeIndexes(const std::vector<sizeT>& indexes)const
{
  auto path = Path();
  for(const auto i : indexes)
  {
    path.addNodeToPath(&nodes[i]);
  }
  return path;
}