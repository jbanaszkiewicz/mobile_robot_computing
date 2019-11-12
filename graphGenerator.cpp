#include "graphGenerator.h"
#include <cmath>

realT graphGenerator::getRandomPosition(realT maxValue)
{
  return static_cast <realT> (rand()) / (static_cast <realT> (RAND_MAX/maxValue));
}

std::vector<std::pair<realT, realT>> graphGenerator::generatePoints(sizeT numberOfNodes = 100, realT squereEdgeLength = 1.0)
{
  auto v = std::vector<std::pair<realT, realT>>(numberOfNodes);
  for (sizeT i = 0; i < numberOfNodes; i++)
  {
    v.push_back(std::pair<realT, realT>(getRandomPosition(squereEdgeLength),getRandomPosition(squereEdgeLength)));
  }  
  return v;
}

realT graphGenerator::norm(const Node & a,const Node & b)
{
  auto firstA = a.position.first;
  auto secondA = a.position.second;
  auto firstB = b.position.first;
  auto secondB = b.position.second;

  return sqrt((firstA - firstB)*(firstA - firstB) 
    + (secondA - secondB)*(secondA - secondB));
}

Graph const & graphGenerator::getGraph(sizeT numberOfNodes = 100,realT radiusOfNeighbourhood = 0.1, realT squereEdgeLength = 1.0)
{
  Graph g(numberOfNodes);
  auto randomPoints = generatePoints();

  for (const auto & p : randomPoints)
  {
    g.addNode(p);
  }

  auto nodes = g.getNodes();

  for(const auto & p : nodes)
  {
    for(const auto & q : nodes)
    {
      auto distance = norm(p,q);
      if(&p != &q
        && distance <= radiusOfNeighbourhood)
      {
        g.addEdge(p,q, distance);
      }
    }
  }
}


    // size_t n = numberOfNodes;
    // double a = squereEdgeLength;
    // double r = radiusOfNeighbourhood;