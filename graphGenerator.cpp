#include "graphGenerator.h"
#include <math.h>

graphGenerator::graphGenerator()
{
  srand(0); // for Reproducibility
}

graphGenerator::~graphGenerator()
{
}

realT graphGenerator::getRandomPosition(realT maxValue)
{
  return static_cast <realT> (rand()) / (static_cast <realT> (RAND_MAX/maxValue));
}

std::vector<std::pair<realT, realT>> graphGenerator::generatePoints(
  sizeT numberOfPoints, realT squereEdgeLength)
{
  auto v = std::vector<std::pair<realT, realT>>(numberOfPoints);
  for (sizeT i = 0; i < numberOfPoints; i++)
  {
    v.push_back(std::pair<realT, realT>(getRandomPosition(squereEdgeLength),getRandomPosition(squereEdgeLength)));
  }  
  return v;
}

realT graphGenerator::normSquered(const Node & a,const Node & b)
{
  auto firstA = a.position.first;
  auto secondA = a.position.second;
  auto firstB = b.position.first;
  auto secondB = b.position.second;

  return (firstA - firstB)*(firstA - firstB) 
    + (secondA - secondB)*(secondA - secondB);
}

Graph graphGenerator::getGraph(
  sizeT numberOfNodes,realT radiusOfNeighbourhood, realT squereEdgeLength)
{
  Graph g(numberOfNodes);
  auto randomPoints = generatePoints(numberOfNodes,squereEdgeLength);

  for (const auto & p : randomPoints)
  {
    g.addNode(p);
  }

  auto nodes = g.getNodes();
  auto radiusOfNeighbourhoodSquered = radiusOfNeighbourhood * radiusOfNeighbourhood;

  for(const auto & p : nodes)
  {
    for(const auto & q : nodes)
    {
      auto distanceSquered = normSquered(p,q);
      if(&p != &q
        && distanceSquered <= radiusOfNeighbourhoodSquered)
      {
        g.addEdge(p,q,sqrt(distanceSquered));
      }
    }
  }
}