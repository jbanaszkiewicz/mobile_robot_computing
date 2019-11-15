#include "randomPath.h"
#include "path.h"
#include "graph.h"
RandomPath::RandomPath(/* args */)
{}

RandomPath::~RandomPath()
{}

std::vector<Path> RandomPath::getRandomPaths(
  const Graph & graph, sizeT numberOfPaths,const Node& start,const Node& destination)
{
  throw std::logic_error("getRandomPaths Not Implemented");
  return std::vector<Path>();
}