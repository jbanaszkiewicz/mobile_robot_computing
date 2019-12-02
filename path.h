#ifndef PATH_H
#define PATH_H
#include <vector>
#include "graph.h"
class Node;

//TODO: ADAM Napisać jakieś pola/tworzenie ścieżki
class Path
{
public:
  Path(/* args */);
  ~Path();
  const Node* getNode(size_t i)const;
  std::vector<const Node*> nodes;
  realT getLength()const;
};

#endif // PATH_H