#include <algorithm> // std::max_element
#include "psoPathSearch.h"
#include "randomPath.h"

PsoPathSearch::PsoPathSearch(const Graph & graph,const Node& start,const Node& destination)
:graph(graph),
start(start),
destination(destination)
{}

PsoPathSearch::~PsoPathSearch()
{}

std::pair<Path,costT> PsoPathSearch::FindShortestPath(
  sizeT numberOfParticles, sizeT maximumIterations = 500)const
{ 
  std::vector<Particle> particles = getParticles( numberOfParticles );

  std::pair<Path,costT> bestSolution = std::pair<Path,costT>(); // g, gBest

  for(sizeT i = 0; i < maximumIterations; ++i)
  {
    particles = updateParticles(particles, bestSolution);
    bestSolution = getBestSolution(particles,bestSolution);
  }

  return bestSolution;
}

std::vector<Particle> PsoPathSearch::getParticles(
  sizeT numberOfParticles )const
{
  auto randomPaths = RandomPath::getRandomPaths(graph, numberOfParticles, start, destination);
  auto particles = std::vector<Particle>(numberOfParticles);

  for (sizeT i = 0; i < numberOfParticles; i++)
  {
    auto pathLength = graph.getPathLength(randomPaths[i]);
    particles[i] = Particle(randomPaths[i],pathLength);
  }
  return particles;
}

std::pair<Path,costT>  PsoPathSearch::getBestSolution(
  const std::vector<Particle> & particles,std::pair<Path,costT> bestSolution)const
{
  auto bestParticle =  std::max_element(particles.begin(),particles.end(),[](Particle l, Particle r) { 
        return l.bestCost > r.bestCost; 
    });

  if (bestSolution.second >= bestParticle->bestCost)
  {
    return bestSolution;
  } 
  return std::pair<Path,costT>(bestParticle->bestPath,bestParticle->bestCost);
}

std::vector<Particle> PsoPathSearch::updateParticles(
  std::vector<Particle>& particles,const std::pair<Path,costT>& bestSolution)const
{
  for(auto & p : particles)
  {
    updateParticle(p,bestSolution);
  } 
  return particles;
}

Particle PsoPathSearch::updateParticle(
  Particle& particle,const std::pair<Path,costT>& bestSolution)const
{
  Path newPath = Path();
  
  const auto* current = &start;
  size_t i = 1;
  do
  {
    newPath.nodes.push_back(current);
    
    //auto neighbours = getNeighbours(current);

    //current = getNeighbourClosestTo(neighbours,bestSolution.first.getNode(i), particle.bestPath.getNode(i));

  }while (1/*from start to finish*/);
  


  particle.currentPath = newPath;
  return particle;
}

  // particle.currentPath;
  // particle.bestPath;
  // bestSolution.first
  // Path updatedPath;
  // while (1/*from start to finish*/)
  // {
    
  // }
