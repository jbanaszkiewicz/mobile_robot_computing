#include <algorithm> // std::max_element
#include "psoPathSearch.h"
#include "randomPath.h"
#include "graphGenerator.h"
#include <omp.h>

PsoPathSearch::PsoPathSearch(const Graph & graph,const Node& start,const Node& destination)
:graph(graph),
start(start),
destination(destination)
{}

PsoPathSearch::~PsoPathSearch()
{}

std::pair<Path,costT> PsoPathSearch::FindShortestPath(
  sizeT numberOfParticles, sizeT maximumIterations = 500)
{ 
  std::vector<Particle> particles = getParticles( numberOfParticles );
  const auto firstParticle = particles.front();
  const auto anySolution = std::pair<Path,costT>(firstParticle.currentPath, firstParticle.currentCost);
  std::pair<Path,costT> bestSolution = getBestSolution(particles,anySolution ); // g, gBest

  maxPathLenght = getMaxPathLenght(particles);
  //TODO: KUBA zwrownoleglic OpenMP
  // #pragma omp paralell for
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
  //TODO: KUBA to bedzie zwronoleglone
  auto randomPaths = RandomPath::getRandomPaths(graph, numberOfParticles, start, destination);
  auto particles = std::vector<Particle>(numberOfParticles);

  for (sizeT i = 0; i < numberOfParticles; i++)
  {
    //TODO: KUBA zrownoleglic przypisywanie OpenMP
    auto pathLength = randomPaths[i].getLength();
    particles[i] = Particle(randomPaths[i],pathLength);
  }
  return particles;
}

std::pair<Path,costT>  PsoPathSearch::getBestSolution(
  const std::vector<Particle> & particles,std::pair<Path,costT> bestSolution)const
{
  // https://en.cppreference.com/w/cpp/algorithm/min_element
  auto bestParticle =  std::min_element(particles.begin(),particles.end(),
    [](Particle l, Particle r) { 
        return l.bestCost < r.bestCost; 
    });

  if (bestSolution.second <= bestParticle->bestCost)
  {
    return bestSolution;
  } 
  return std::pair<Path,costT>(bestParticle->bestPath,bestParticle->bestCost);
}

sizeT PsoPathSearch::getMaxPathLenght(const std::vector<Particle>& particles) const
{
  auto particleWithLongestPath =  std::max_element(particles.begin(),particles.end(),
    [](Particle l, Particle r) { 
      return l.currentPath.nodes.size() < r.currentPath.nodes.size(); 
  });
  return particleWithLongestPath->currentPath.nodes.size();
}

std::vector<Particle> PsoPathSearch::updateParticles(
  std::vector<Particle>& particles,const std::pair<Path,costT>& bestSolution)const
{
  for(auto & p : particles)
  {
    const auto newPath = getNextPath(p,bestSolution);
    p.setPath(newPath);
  } 
  return particles;
}

Path PsoPathSearch::getNextPath(
  const Particle& particle,const std::pair<Path,costT>& bestSolution)const
{
  Path newPath = Path();
  
  const auto* current = &start;
  newPath.nodes.push_back(current);
  size_t i = 1;
  do
  {
    auto neighbours = graph.getNeighbours(current);

    current = getNeighbourClosestTo(neighbours,bestSolution.first.getNode(i), particle.bestPath.getNode(i));

    newPath.nodes.push_back(current);
    ++i;
    if(newPath.nodes.size() > maxPathLenght)
    {
      newPath = particle.currentPath;
      break;
    }
  }while (current != &destination);
  
  return newPath;
}

const Node* PsoPathSearch::getNeighbourClosestTo(
  std::pair<mapT::const_iterator,mapT::const_iterator> neighbours,
  const Node* globalBestPathNode,
  const Node* particelBestPathNode
  )const
{
  auto closestNeighbour = neighbours.first;
  auto smallestNorm = GraphGenerator::normSquered(*(*closestNeighbour).second.first,*globalBestPathNode) 
    + GraphGenerator::normSquered(*(*closestNeighbour).second.first,*particelBestPathNode);

  for( auto i =  neighbours.first; i != neighbours.second; ++i)
  {
    auto norm = GraphGenerator::normSquered(*(*i).second.first,*globalBestPathNode) 
        + GraphGenerator::normSquered(*(*i).second.first,*particelBestPathNode);
    if(norm < smallestNorm)
    {
      closestNeighbour = i;
      smallestNorm = norm;
    }
  }
    return (*closestNeighbour).second.first;
}

void Particle::setPath(const Path& path)
{
  currentPath = path; 
  currentCost = path.getLength();
  if(currentCost < bestCost)
  {
    bestCost = currentCost;
    bestPath = currentPath;
  }
}