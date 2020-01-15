#include <algorithm> // std::max_element
#include <cuda_runtime_api.h>
#include <cuda.h>
#include <ecuda/ecuda.hpp>

#include "psoPathSearchGPU.h"
#include "randomPath.h"
#include "graphGenerator.h"
#include "graphGPU.h"

PsoPathSearch::PsoPathSearchGPU(const graphGPU & graph,const Node& start,const Node& destination)
:graph(graph),
start(start),
destination(destination)
{}

PsoPathSearch::~PsoPathSearch()
{}

ecuda::pair<Path,costT> PsoPathSearch::FindShortestPath(
  sizeT numberOfParticles, sizeT maximumIterations = 500)
{ 
  ecuda::vector<Particle> particles = getParticles( numberOfParticles );
  const auto firstParticle = particles.front();
  const auto anySolution = std::pair<Path,costT>(firstParticle.currentPath, firstParticle.currentCost);
  std::pair<Path,costT> bestSolution = getBestSolution(particles,anySolution ); // g, gBest

  maxPathLenght = getMaxPathLenght(particles);
    // CUDA_CALL_KERNEL_AND_WAIT(<<<>>>)



  return bestSolution;
}

  // może nie wracać po każdej iteracji do cpu tylko wiele iteracji na gpu?
__global__
  // outArgs 
  
  // inArhs
{
  sizeT i = 0;
  while( i < maximumIterations)
  {
    particles = updateParticles(particles, bestSolution);
    bestSolution = getBestSolution(particles,bestSolution);
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index == 0)
    {
      ++i;
    } 
  }
}
__global__
void generateParticles(typename ecuda::vector<Particle>::kernel_argument & particlesGPU, typename ecuda::vector<Path>::const_kernel_argument& randomPathsGPU, sizeT numberOfParticles)
{
  // czy trzeba przekazać graph
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;
  for (int i = index; i < numberOfParticles; i += stride)
  {
    auto pathLength = randomPathsGPU[i].getLength();
    particlesGPU[i] = Particle(randomPathsGPU[i],pathLength);
  }

}

std::vector<Particle> PsoPathSearch::getParticles(
  sizeT numberOfParticles )const
{
  auto randomPaths = RandomPath::getRandomPaths(graph, numberOfParticles, start, destination);
  auto particles = std::vector<Particle>(numberOfParticles);

  ecuda::vector<Particle> particlesGPU (particles.begin(), particles.end());
  ecuda::vector<Path> randomPathsGPU (randomPaths.begin(), randomPaths.end());
  
  generateParticles<<<1, 1>>>(particlesGPU, randomPathsGPU, numberOfParticles);
  
  ecuda::copy(particlesGPU.begin(), particlesGPU.end(), particles.begin());

  return particles;
}

std::pair<Path,costT>  PsoPathSearch::getBestSolution(
  const std::vector<Particle> & particles,std::pair<Path,costT> bestSolution)const
{
  // warto zrownoleglic swoim kodem albo z thrust 
  //
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

__device__
std::vector<Particle> PsoPathSearch::updateParticles(
  std::vector<Particle>& particles,const std::pair<Path,costT>& bestSolution)const
{
  // czy trzeba przekazać graph
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;
  for (int i = index; i < particles.size(); i += stride)
  {
    const auto newPath = getNextPath(particles[i],bestSolution);
    particles[i].setPath(newPath);
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