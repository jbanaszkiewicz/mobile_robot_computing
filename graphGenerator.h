#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H
#include <stddef.h>  /* size_t */
#include <stdlib.h>  /* srand, rand */
#include <vector>
#include <utility>  /* pair */
#include "graph.h"
// #include <time.h>       /* time */

// https://en.wikipedia.org/wiki/Random_geometric_graph
// Generates graph by
// generates random point in unit size squere with nonnegative coords
// conects ones in Neighbourhood given by radius
using realT = double;
using sizeT = size_t;

class graphGenerator
{
private:
  realT getRandomPosition(realT maxValue);
  std::vector<std::pair<realT, realT>>  generatePoints(sizeT numberOfNodes = 100, realT squereEdgeLength = 1.0);
  realT norm(const std::pair<realT,realT> & a,const std::pair<realT,realT> & b );
public:
  graphGenerator();
  ~graphGenerator();
  Graph const & getGraph(sizeT numberOfNodes = 100,realT radiusOfNeighbourhood = 0.1, realT squereEdgeLength = 1.0);
};

graphGenerator::graphGenerator()
{
  srand(NULL); // for Reproducibility
}

graphGenerator::~graphGenerator()
{
}


#endif //GRAPH_GENERATOR_H
