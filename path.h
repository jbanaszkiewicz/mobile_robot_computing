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

  std::vector<const Node*> nodes;
};

#endif // PATH_H