#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H
#include <stddef.h>  /* size_t */
#include <stdlib.h>  /* srand, rand */
#include <vector>
#include <utility>  /* pair */
#include "graph.h"
// #include <time.h> /* time */

// https://en.wikipedia.org/wiki/Random_geometric_graph
// Generuje graf przez
// Wygenerowanie losowych punktów w kwadracie o wierzchołkach (0,0), (1,0), (0,1) i (1,1) 
// Łączy wierzchołki jeżeli są odległe o nie wiecej niż podany promień sąsiedztwa radiusOfNeighbourhood
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
  static Graph addEdges(Graph g,realT radiusOfNeighbourhood);

};
#endif //GRAPH_GENERATOR_H
