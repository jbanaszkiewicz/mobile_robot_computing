#ifndef PATH_H
#define PATH_H
#include <vector>
#include "graphGPU.h"
#include <ecuda/ecuda.hpp>

class Node;

class Path
{
public:
  ecuda::vector<const Node*> nodes;

  Path();
  ~Path();
  const Node* getNode(size_t i)const;
  realT getLength()const;
  void addNodeToPath(const Node* node);
};

class PathGPU
{
public:
  ecuda::vector<const Node*> nodes;

  PathGPU();
  PathGPU(Path path);
  ~PathGPU();
  const Node* getNode(size_t i)const;
  realT getLength()const;
  void addNodeToPath(const Node* node);
};

#endif // PATH_H