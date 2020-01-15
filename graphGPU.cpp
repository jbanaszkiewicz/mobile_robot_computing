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
  ecuda::copy(graphEdges.begin(),graphEdges.end(),edges.begin() );
  
}
__device__
GraphGPU::~GraphGPU()
{
}
__device__
const ecuda::vector<Node>& GraphGPU::getNodes()const
{
  return nodes;
}

__device__
ecuda::vector< valueT> GraphGPU::getNeighboursVector(
  const sizeT node)const
{
  return edges[node];
}

