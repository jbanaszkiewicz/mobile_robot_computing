#include "graphGPU.h"
__device__
realT NodeGPU::getPositionX()const
{
  return this->position.first;
}

__device__
realT NodeGPU::getPositionY()const
{
  return this->position.second;
}

__device__
void NodeGPU::setPositionX(realT x)
{
  this->position.first = x;
}

__device__
void NodeGPU::setPositionY(realT y)
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
GraphGPU::~GraphGPU()
{
}
__device__
ecuda::vector<NodeGPU> GraphGPU::getNodes()const
{
  return nodes;
}

__device__
ecuda::vector< edgeT> GraphGPU::getNeighboursVector(
  const sizeT node)
{
  return edges[node];
}

