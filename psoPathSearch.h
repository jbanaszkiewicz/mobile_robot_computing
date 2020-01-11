#ifndef PSO_PATH_SEARCH
#define PSO_PATH_SEARCH

#include <vector>
#include "graph.h"
#include "path.h"

using costT = realT;
using sizeT = size_t;
using solutionT = std::pair<Path,costT>;

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


  void setPath(const Path& path);
};


class PsoPathSearch
{
public:
  PsoPathSearch(const Graph & graph,const Node& start,const Node& destination);
  ~PsoPathSearch();
  solutionT FindShortestPath(
    sizeT numberOfPartiles, sizeT maximumIterations);
private:
  const Graph& graph;
  const Node& start;
  const Node& destination;

  sizeT maxPathLenght;

  const static int SERVER_HOST = 0;

  std::vector<Particle> getParticles(
    sizeT numberOfParticles)const;
  solutionT getBestSolution(
    const std::vector<Particle> & particles,solutionT bestSolution)const;
  std::vector<Particle> updateParticles(
    std::vector<Particle>& particles,const solutionT& bestSolution)const;
  Path getNextPath(
    const Particle& particle,const solutionT& bestSolution)const;
  const Node* getNeighbourClosestTo(
    std::pair<mapT::const_iterator,mapT::const_iterator> neighbours,
    const Node* globalBestPathNode,
    const Node* particelBestPathNode
    )const; 
  sizeT getMaxPathLenght(const std::vector<Particle>& particles) const;
  friend class PsoTests;

  solutionT getBestSolutionMPI(
    solutionT bestSolution)const;
  solutionT bestSolutionServer(
    solutionT bestSolution)const;
  solutionT bestSolutionClient(
    solutionT bestSolution)const;
  void sendPathTo(const Path & path, int host)const;
  Path receivePathFrom(int host)const;
  void broadcastPathAs(const Path & path, int host)const;
};

#endif // PSO_PATH_SEARCH
