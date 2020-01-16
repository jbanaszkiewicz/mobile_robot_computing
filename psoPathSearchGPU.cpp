#include <algorithm> // ecuda::max_element
#include <cuda_runtime_api.h>
#include <cuda.h>
#include <ecuda/ecuda.hpp>

#include "psoPathSearchGPU.h"
#include "randomPath.h"
#include "graphGenerator.h"
#include "graphGPU.h"
__global__
PsoPathSearchGPU::PsoPathSearchGPU(const graphGPU & graph,const Node& start,const Node& destination)
:graph(graph),
start(start),
destination(destination)
{}
__global__
PsoPathSearchGPU::~PsoPathSearchGPU()
{}
__global__
ecuda::pair<Path,costT> PsoPathSearchGPU::FindShortestPath(
  sizeT numberOfParticles, sizeT maximumIterations = 500)
{ 
  ecuda::vector<ParticleGPU> particlesGPU = getParticles( numberOfParticles );
  const auto firstParticleGPU = particlesGPU.front();
  const auto anySolution = ecuda::pair<Path,costT>(firstParticleGPU.currentPath, firstParticleGPU.currentCost);
  ecuda::pair<Path,costT> bestSolution = getBestSolution(particlesGPU,anySolution ); // g, gBest

  maxPathLenght = getMaxPathLenght(particlesGPU);
    // CUDA_CALL_KERNEL_AND_WAIT(<<<>>>)



  return bestSolution;
}

  // może nie wracać po każdej iteracji do cpu tylko wiele iteracji na gpu?

  // outArgs 
  
  // inArhs

__global__
void generateParticles(typename ecuda::vector<ParticleGPU>::kernel_argument & particlesGPU, typename ecuda::vector<Path>::const_kernel_argument& randomPathsGPU, sizeT numberOfParticles)
{
  // czy trzeba przekazać graph
  int index = blockIdx.x * blockDim.x + threadIdx.x;
  int stride = blockDim.x * gridDim.x;
  for (int i = index; i < numberOfParticles; i += stride)
  {
    auto pathLength = randomPathsGPU[i].getLength();
    particlesGPU[i] = ParticleGPU(randomPathsGPU[i],pathLength);
  }

}
__global__
ecuda::vector<ParticleGPU> PsoPathSearch::getParticles(
  sizeT numberOfParticles )const
{
  auto randomPaths = RandomPath::getRandomPaths(graph, numberOfParticles, start, destination);
  auto particles = ecuda::vector<ParticleGPU>(numberOfParticles);

  ecuda::vector<ParticleGPU> particlesGPU (particles.begin(), particles.end());
  ecuda::vector<Path> randomPathsGPU (randomPaths.begin(), randomPaths.end());
  
  generateParticles<<<1, 1>>>(particlesGPU, randomPathsGPU, numberOfParticles);
  
  ecuda::copy(particlesGPU.begin(), particlesGPU.end(), particles.begin());

  return particles;
}
__global__
ecuda::pair<Path,costT>  PsoPathSearch::getBestSolution(
  const ecuda::vector<ParticleGPU> & particles,ecuda::pair<Path,costT> bestSolution)const
{
  // warto zrownoleglic swoim kodem albo z thrust 
  //
  // https://en.cppreference.com/w/cpp/algorithm/min_element
  auto bestParticle =  ecuda::min_element(particles.begin(),particles.end(),
    [](ParticleGPU l, ParticleGPU r) { 
        return l.bestCost < r.bestCost; 
    });

  if (bestSolution.second <= bestParticle->bestCost)
  {
    return bestSolution;
  } 
  return ecuda::pair<Path,costT>(bestParticle->bestPath,bestParticle->bestCost);
}
__global__
sizeT PsoPathSearch::getMaxPathLenght(const ecuda::vector<Particle>& particles) const
{
  auto particleWithLongestPath =  ecuda::max_element(particles.begin(),particles.end(),
    [](Particle l, Particle r) { 
      return l.currentPath.nodes.size() < r.currentPath.nodes.size(); 
  });
  return particleWithLongestPath->currentPath.nodes.size();
}

__global__
ecuda::vector<ParticleGPU> PsoPathSearch::updateParticles(
  ecuda::vector<ParticleGPU>& particles,const ecuda::pair<Path,costT>& bestSolution)const
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

__global__
void operateOnParticle(typename ecuda::vector<ParticleGPU>::kernel_argument & particles, const ecuda::pair<Path,costT>& bestSolution, sizeT  maximumIterations)
{
  sizeT i = 0;
  while( i < maximumIterations)
  {
    particlesGPU = updateParticles(particlesGPU, bestSolution);
    bestSolution = getBestSolution(particlesGPU,bestSolution);
    int index = blockIdx.x * blockDim.x + threadIdx.x;
    if(index == 0)
    {
      ++i;
    } 
  }
}

__global__
PathGPU PsoPathSearch::getNextPath(
  const ParticleGPU& particle,const ecuda::pair<PathGPU,costT>& bestSolution)const
{
  PathGPU newPath = PathGPU();
  
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
__global__
const Node* PsoPathSearch::getNeighbourClosestTo(
  ecuda::pair<mapT::const_iterator,mapT::const_iterator> neighbours,
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
__global__
void ParticleGPU::setPath(const PathGPU& pathGPU)
{
  currentPath = pathGPU; 
  currentCost = pathGPU.getLength();
  if(currentCost < bestCost)
  {
    bestCost = currentCost;
    bestPath = currentPath;
  }
}