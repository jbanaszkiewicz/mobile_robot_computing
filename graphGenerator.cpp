#include "graphGenerator.h"
#include <cmath>

realT getRandomPosition(realT maxValue)
{
  return static_cast <realT> (rand()) / (static_cast <realT> (RAND_MAX/maxValue));
}

std::vector<std::pair<realT, realT>>  generatePoints(sizeT numberOfNodes = 100, realT squereEdgeLength = 1.0)
{
  auto v = std::vector<std::pair<realT, realT>>(numberOfNodes);
  for (sizeT i = 0; i < numberOfNodes; i++)
  {
    v.push_back(std::pair<realT, realT>(getRandomPosition(squereEdgeLength),getRandomPosition(squereEdgeLength)));
  }  
  return v;
}

realT norm(const std::pair<realT,realT> & a,const std::pair<realT,realT> & b )
{
  return sqrt((a.first - b.first)*(a.first - b.first) 
    + (a.second - b.second)*(a.second - b.second));
}

Graph const & getGraph(sizeT numberOfNodes = 100,realT radiusOfNeighbourhood = 0.1, realT squereEdgeLength = 1.0)
{
  Graph g(numberOfNodes);
  auto randomPoints = generatePoints();
  for(const auto & p : randomPoints)
  {
    for(const auto & q : randomPoints)
    {
      auto distance = norm(p,q);
      if(p != q
      && distance <= radiusOfNeighbourhood)
      {
        g.
      }
    }
  }
}


    // size_t n = numberOfNodes;
    // double a = squereEdgeLength;
    // double r = radiusOfNeighbourhood;