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
  PsoPathSearch(const Graph & graph,const Node& start,const Node& destination);
  ~PsoPathSearch();
  std::pair<Path,costT> FindShortestPath(
    sizeT numberOfPartiles, sizeT maximumIterations)const;
private:
  const Graph& graph;
  const Node& start;
  const Node& destination;

  std::vector<Particle> getParticles(
    sizeT numberOfParticles)const;
  std::pair<Path,costT> getBestSolution(
    const std::vector<Particle> & particles,std::pair<Path,costT> bestSolution)const;
  std::vector<Particle> updateParticles(
    std::vector<Particle>& particles,const std::pair<Path,costT>& bestSolution)const;
  Particle updateParticle(
    Particle& particle,const std::pair<Path,costT>& bestSolution)const;
  const Node* getNeighbourClosestTo(
    std::pair<mapT::const_iterator,mapT::const_iterator> neighbours,
    const Node* globalBestPathNode,
    const Node* particelBestPathNode
    )const; 
  friend class PsoTests;
};

#endif // PSO_PATH_SEARCH
