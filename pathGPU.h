#ifndef PATH_GPU
#define PATH_GPU
#include <vector>
#include "graphGPU.h"
#include <ecuda/ecuda.hpp>

class Node;

class PathGPU
{
public:
  ecuda::vector<const Node*> nodes;

  PathGPU();
  ~PathGPU();
  const Node* getNode(size_t i)const;
  realT getLength()const;
  void addNodeToPath(const Node* node);
};


#endif // PATH_GPU