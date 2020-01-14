#include "graphGPU.h"
__device__
realT Node::getPositionX()const
{
  return this->position.first;
}

__device__
realT Node::getPositionY()const
{
  return this->position.second;
}

__device__
void Node::setPositionX(realT x)
{
  this->position.first = x;
}

__device__
void Node::setPositionY(realT y)
{
  this->position.second = y;
}

GraphGPU::GraphGPU(Graph g)
{
  const auto& graphNodes = g.getNodes(); 
  ecuda::copy(graphNodes.begin(),graphNodes.end(),nodes.begin() );

  const auto& graphEdges = g.getEdges(); 
  // skopiowac krawedzie
  // ecuda::copy(graphEdges.begin(),graphEdges.end(),edges.begin() );
  
}
__device__
GraphGPU::~GraphGPU()
{
}
__device__
const std::vector<Node>& GraphGPU::getNodes()const
{
  return nodes;
}

__device__
std::pair<mapT::const_iterator,mapT::const_iterator>
  GraphGPU::getNeighbours(const Node* node)const
{
  return edges.equal_range( node);
}

__device__
std::vector<const Node*> GraphGPU::getNeighboursVector(
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
