#include "path.h"

Path::Path(/* args */)
{
}

Path::~Path()
{
}

const Node* Path::getNode(size_t i)const
{
  if(i >=  nodes.size())
  {
    return nodes.back();
  }
  return nodes[i];
}