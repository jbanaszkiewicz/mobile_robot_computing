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

realT Path::getLength()const
{
  //TODO: ADAM napisac kod pod dlugosc sciezki
  throw std::logic_error("getPathLength Not Implemented");
  return realT();
}