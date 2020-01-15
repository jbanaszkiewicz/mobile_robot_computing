#ifndef PATH_H
#define PATH_H
#include <vector>
#include "graph.h"
#include <ecuda/ecuda.hpp>

class Node;

class Path
{
public:
  std::vector<const Node*> nodes;

  Path();
  ~Path();
  const Node* getNode(size_t i)const;
  realT getLength()const;
  void addNodeToPath(const Node* node);
};


#endif // PATH_H