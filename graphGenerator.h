#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H
#include <stddef.h>  /* size_t */
#include <stdlib.h>  /* srand, rand */
#include <vector>
#include <utility>  /* pair */
#include "graph.h"
// #include <time.h> /* time */

// https://en.wikipedia.org/wiki/Random_geometric_graph
// Generates graph by
// generates random point in unit size squere with nonnegative coords
// conects ones in Neighbourhood given by radius
using realT = double;
using sizeT = size_t;

class graphGenerator
{
private:
  static realT getRandomPosition(realT maxValue);
  static std::vector<std::pair<realT, realT>>  generatePoints(
    sizeT numberOfNodes, realT squereEdgeLength);
  static realT normSquered(const Node & a,const Node & b);
public:
  graphGenerator();
  ~graphGenerator();
  static Graph getGraph(
    sizeT numberOfNodes = 100,realT radiusOfNeighbourhood = 0.1, realT squereEdgeLength = 1.0);
};
#endif //GRAPH_GENERATOR_H
