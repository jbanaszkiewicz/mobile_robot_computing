#include "graphGenerator.h"
#include <math.h>

GraphGenerator::GraphGenerator()
{
  srand(0); // for Reproducibility
}

GraphGenerator::~GraphGenerator()
{
}

realT GraphGenerator::getRandomPosition(realT maxValue)
{
  return static_cast <realT> (rand()) / (static_cast <realT> (RAND_MAX/maxValue));
}

std::vector<pointT> GraphGenerator::generatePoints(
  sizeT numberOfPoints, realT squereEdgeLength)
{
  auto v = std::vector<pointT>();
  v.reserve(numberOfPoints);

  realT realTZero = static_cast<realT>(0.0);
  v.push_back(pointT(realTZero,realTZero));
  v.push_back(pointT(squereEdgeLength,squereEdgeLength));

  for (sizeT i = 2; i < numberOfPoints; i++)
  {
    v.push_back(pointT(getRandomPosition(squereEdgeLength),getRandomPosition(squereEdgeLength)));
  }  
  return v;
}

realT GraphGenerator::normSquered(const Node & a,const Node & b)
{
  auto firstA = a.position.first;
  auto secondA = a.position.second;
  auto firstB = b.position.first;
  auto secondB = b.position.second;

  return (firstA - firstB)*(firstA - firstB) 
    + (secondA - secondB)*(secondA - secondB);
}

Graph GraphGenerator::getGraph(
  sizeT numberOfNodes,realT radiusOfNeighbourhood, realT squereEdgeLength)
{
  auto graph = addNodes(numberOfNodes, squereEdgeLength);
  return addEdges(graph,radiusOfNeighbourhood);
  
}

Graph GraphGenerator::addNodes(sizeT numberOfNodes, realT squereEdgeLength)
{
  Graph g(numberOfNodes);
  auto randomPoints = generatePoints(numberOfNodes,squereEdgeLength);

  for (const auto & p : randomPoints)
  {
    g.addNode(p);
  }
  return g;
}
Graph GraphGenerator::addEdges(Graph g,realT radiusOfNeighbourhood)
{
  const auto & nodes = g.getNodes();
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

  return g;
}
const Node& GraphGenerator::getStart(const Graph & graph)
{
  return graph.getNodes()[0];
}
const Node& GraphGenerator::getDestination(const Graph & graph)
{
  return graph.getNodes()[1];
}