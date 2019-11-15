#include <algorithm> // std::max_element
#include "psoPathSearch.h"
#include "randomPath.h"

PsoPathSearch::PsoPathSearch()
{}

PsoPathSearch::~PsoPathSearch()
{}

std::pair<Path,costT> PsoPathSearch::FindShortestPath(
  const Graph & graph,sizeT numberOfParticles,const Node& start,const Node& destination, sizeT maximumIterations = 500)
{ 
  std::vector<Particle> particles = getParticles(graph, numberOfParticles, start, destination);

  std::pair<Path,costT> bestSolution = std::pair<Path,costT>(); // g, gBest

  for(sizeT i = 0; i < maximumIterations; ++i)
  {
    particles = updateParticles(graph, particles, bestSolution);
    bestSolution = getBestSolution(particles,bestSolution);
  }

  return bestSolution;
}

std::vector<Particle> PsoPathSearch::getParticles(
  const Graph & graph, sizeT numberOfParticles,const Node& start,const Node& destination )
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
  const std::vector<Particle> & particles,std::pair<Path,costT> bestSolution)
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
  const Graph & graph,std::vector<Particle>& particles,const std::pair<Path,costT>& bestSolution)
{
  for(auto & p : particles)
  {
    updateParticle(graph,p,bestSolution);
  } 
  return particles;
}

Particle PsoPathSearch::updateParticle(
  const Graph & graph,Particle& particle,const std::pair<Path,costT>& bestSolution)
{
  // particle.currentPath;
  // particle.bestPath;
  // bestSolution.first
  // Path updatedPath;
  // while (1/*from start to finish*/)
  // {
    
  // }
  return particle;
}