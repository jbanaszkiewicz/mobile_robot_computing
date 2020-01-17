#include "pathGPU.h"
#include <cmath>
#include <cuda_runtime_api.h>
#include <cuda.h>
#include <ecuda/ecuda.hpp>
__global__
PathGPU::~PathGPU()
{
}
__global__
const Node* PathGPU::getNode(size_t i)const
{
  if(i >=  nodes.size())
  {
    return nodes.back();
  }
  return nodes[i];
}
__global__
realT PathGPU::getLength()const
{
  realT length = 0;
  realT partialLength = 0;

  realT previousX = this->nodes.at(0)->getPositionX();
  realT previousY = this->nodes.at(0)->getPositionY();
  realT currentX, currentY;

  for (auto i = 1; i < this->nodes.size(); i++)
  {
    currentX = this->nodes.at(i)->getPositionX();
    currentY = this->nodes.at(i)->getPositionY();

    partialLength = sqrt( pow( currentX - previousX, 2 ) + pow( currentY - previousY, 2 ) );
    length += partialLength;

    if (i != (this->nodes.size() - 1))
    {
      previousX = currentX;
      previousY = currentY;
    }
  }

  return length;
}
__global__
void PathGPU::addNodeToPath(const Node* node)
{
  this->nodes.push_back(node);
}