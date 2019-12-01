#ifndef PATH_H
#define PATH_H
#include <vector>
#include "graph.h"
class Node;

//TODO: zadeklarowac funkcje do liczenia dlugosci sciezki ADAM
class Path
{
public:
  Path(/* args */);
  ~Path();
  const Node* getNode(size_t i)const;
  std::vector<const Node*> nodes;
};

#endif // PATH_H