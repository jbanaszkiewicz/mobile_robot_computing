#ifndef RANDOM_PATH_H
#define RANDOM_PATH_H
#include <vector>
#include <stddef.h>

class Graph;
class Node;
class Path;
using sizeT = size_t;

// Klasa odpowiadająca losowej ścieżce
class RandomPath
{
public:
  RandomPath();
  ~RandomPath();

  static std::vector<Path> getRandomPaths(
    const Graph & graph, sizeT numberOfPaths,const Node& start,const Node& destination);
};
#endif // RANDOM_PATH_H