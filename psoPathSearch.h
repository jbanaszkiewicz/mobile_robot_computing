#ifndef PSO_PATH_SEARCH
#define PSO_PATH_SEARCH

#include <vector>
#include "graph.h"
#include "path.h"

using costT = realT;
using sizeT = size_t;

class Particle
{  
public:
  Path bestPath; // p
  costT bestCost; // pBest
  Path currentPath;
  costT currentCost;

  Particle()
  {}

  Particle(const Path & path,const costT  pathLength)
  :bestPath(path),
  bestCost(pathLength),
  currentPath(path),
  currentCost(pathLength)
  {}

  ~Particle()
  {}
};


class PsoPathSearch
{
public:
  PsoPathSearch();
  ~PsoPathSearch();
  static std::pair<Path,costT> FindShortestPath(
    const Graph & graph,sizeT numberOfPartiles,const Node& start,const Node& destination, sizeT maximumIterations);
private:
  static std::vector<Particle> getParticles(
    const Graph & graph, sizeT numberOfPartiles,const Node& start,const Node& destination );
  static std::pair<Path,costT> getBestSolution(
    const std::vector<Particle> & particles,std::pair<Path,costT> bestSolution);
  static std::vector<Particle> updateParticles(
    const Graph & graph,std::vector<Particle>& particles,const std::pair<Path,costT>& bestSolution);
  static Particle updateParticle(
    const Graph & graph,Particle& particle,const std::pair<Path,costT>& bestSolution);

};

#endif // PSO_PATH_SEARCH
