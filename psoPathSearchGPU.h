#ifndef PSO_PATH_SEARCH_GPU
#define PSO_PATH_SEARCH_GPU

#include <vector>
#include "graphGPU.h"
#include "pathGPU.h"

using costT = realT;
using sizeT = size_t;

class ParticleGPU;
{  
public:
  PathGPU bestPathPU; 
  costT bestCost; // pBest
  Path currentPath;
  costT currentCost;

  ParticleGPU()
  {}

  ParticleGPU(const Path & path,const costT  pathLength)
  :bestPath(path),
  bestCost(pathLength),
  currentPath(path),
  currentCost(pathLength)
  {}

  ~ParticleGPU()
  {}


  void setPath(const Path& path);
};


class PsoPathSearchGPU
{
public:
  __device__
  PsoPathSearchGPU(const GraphGPU & graph,const NodeGPU& start,const NodeGPU& destination);
  ~PsoPathSearchGPU();
  ecuda::pair<Path,costT> FindShortestPath(
    sizeT numberOfPartiles, sizeT maximumIterations);
private:
  const GraphGPU& GraphGPU;
  const NodeGPU& start;
  const NodeGPU& destination;

  sizeT maxPathLenght;

  ecuda::vector<ParticleGPU> getParticles(
    sizeT numberOfParticles)const;
  ecuda::pair<Path,costT> getBestSolution(
    const ecuda::vector<ParticleGPU> & particles,ecuda::pair<PathGPU,costT> bestSolution)const;
  ecuda::vector<ParticleGPU> updateParticles(
    ecuda::vector<ParticleGPU>& particles,const ecuda::pair<PathGPU,costT>& bestSolution)const;
  Path getNextPath(
    const ParticleGPU& particle,const ecuda::pair<PathGPU,costT>& bestSolution)const;
  const Node* getNeighbourClosestTo(
    ecuda::pair<mapT::const_iterator,mapT::const_iterator> neighbours,
    const Node* globalBestPathNode,
    const Node* particelBestPathNode
    )const; 
  sizeT getMaxPathLenght(const ecuda::vector<ParticleGPU>& particles) const;
  friend class PsoTests;
};

#endif // PSO_PATH_SEARCH_GPU
