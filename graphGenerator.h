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
using pointT = std::pair<realT, realT>;

class GraphGenerator
{
private:
  static realT getRandomPosition(realT maxValue);
  static std::vector<pointT>  generatePoints(
    sizeT numberOfNodes, realT squereEdgeLength);
  static Graph addNodes(sizeT numberOfNodes, realT squereEdgeLength);

public:
  GraphGenerator();
  ~GraphGenerator();
  static Graph getGraph(
    sizeT numberOfNodes = 100,realT radiusOfNeighbourhood = 0.1, realT squereEdgeLength = 1.0);
  static const Node& getStart(const Graph & graph);
  static const Node& getDestination(const Graph & graph);
  static realT normSquered(const Node & a,const Node & b);
  static Graph GraphGenerator::addEdges(Graph g,realT radiusOfNeighbourhood);

};
#endif //GRAPH_GENERATOR_H
