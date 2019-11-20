#ifndef PATH_H
#define PATH_H
#include <vector>
#include "graph.h"
class Node;

class Path
{
public:
  Path(/* args */);
  ~Path();
  const Node* getNode(size_t i)const;
  std::vector<const Node*> nodes;
};

#endif // PATH_H