#include <algorithm> // std::max_element
#include <iostream>
#include <mpi.h>
#include "psoPathSearch.h"
#include "randomPath.h"
#include "graphGenerator.h"

PsoPathSearch::PsoPathSearch(const Graph & graph,const Node& start,const Node& destination)
:graph(graph),
start(start),
destination(destination)
{}

PsoPathSearch::~PsoPathSearch()
{}

/*  Zrównoleglenie o jeden posiom wyżej.
    Uzyskujemy grubsze ziarno.
    Zmniejszenie nakładu na komunikacje.
*/
solutionT PsoPathSearch::FindShortestPath(
  sizeT numberOfParticles, sizeT maximumIterations = 500)
{ 
  std::vector<Particle> particles = getParticles( numberOfParticles );
  const auto firstParticle = particles.front();
  const auto anySolution = solutionT(firstParticle.currentPath, firstParticle.currentCost);
  solutionT bestSolution = getBestSolution(particles,anySolution ); // g, gBest

  maxPathLenght = getMaxPathLenght(particles);

  for(sizeT i = 0; i < maximumIterations; ++i)
  {
    particles = updateParticles(particles, bestSolution);
    bestSolution = getBestSolution(particles,bestSolution);
    bestSolution = getBestSolutionMPI(bestSolution); 
  }

  return bestSolution;
}

std::vector<Particle> PsoPathSearch::getParticles(
  sizeT numberOfParticles )const
{
  auto randomPaths = RandomPath::getRandomPaths(graph, numberOfParticles, start, destination);
  auto particles = std::vector<Particle>(numberOfParticles);
  
  // zrównoleglenie poziom wyżej, patrz
  for (sizeT i = 0; i < numberOfParticles; i++)
  {
    auto pathLength = randomPaths[i].getLength();
    particles[i] = Particle(randomPaths[i],pathLength);
  }
  return particles;
}

solutionT  PsoPathSearch::getBestSolution(
  const std::vector<Particle> & particles,solutionT bestSolution)const
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
  return solutionT(bestParticle->bestPath,bestParticle->bestCost);
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
  std::vector<Particle>& particles,const solutionT& bestSolution)const
{
  // zrównoleglenie poziom wyżej, patrz
  for(size_t i = 0; i < particles.size();++i)
  {
    const auto newPath = getNextPath(particles[i],bestSolution);
    particles[i].setPath(newPath);
  } 
  return particles;
}

Path PsoPathSearch::getNextPath(
  const Particle& particle,const solutionT& bestSolution)const
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
/* MPI */
// Zdecyduj jaką rolę ma pełnić proces w MPI
solutionT  PsoPathSearch::getBestSolutionMPI(
  solutionT bestSolution)const
{
  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  //std::cout << "world_rank:"<<world_rank << std::endl;
  if(world_rank == SERVER_HOST)
  {
    bestSolution = bestSolutionServer(bestSolution);
  }else
  {
    bestSolution = bestSolutionClient(bestSolution);
  }
  return bestSolution;
}

// 1. Odbierz najlepsze rozwiązania od wszystkich procesów
// 2. Wybierz najlepsze z pośród nich
// 3. Roześlij najlepsze rozwiązanie
solutionT PsoPathSearch::bestSolutionServer(
  solutionT bestSolution)const
{
  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  auto solutions = std::vector<solutionT>(world_size);
  solutions[0] = bestSolution;
  // 0 to my więc nie odbieramy od siebie
  for (int i = 1; i < world_size; ++i)
  {
    auto path = receivePathFrom(i);
    solutions[i] = solutionT(path, path.getLength());
  }

  bestSolution =  *std::min_element(solutions.begin(),solutions.end(),
    [](solutionT l, solutionT r) { 
      return l.second < r.second; 
  });


  for (int i = 1; i < world_size; ++i)
  {
    sendPathTo(bestSolution.first,i);
  }
  // broadcast wysyła też do siebie,
  // robi to w strukturze drzewiastej
  // chyba się inaczej odbiera
  // broadcastPathAs(bestSolution.first,SERVER_HOST);
  return bestSolution;
}

// 1. Wyślij swoje rozwiązanie do Servera
// 2. Zaczekaj na najlepsze od Servera
// 3. Zapisz najlepjsze rozwiązanie od Servera
solutionT PsoPathSearch::bestSolutionClient(
  solutionT bestSolution)const
{
  sendPathTo(bestSolution.first,SERVER_HOST);
  auto path = receivePathFrom(SERVER_HOST);
  return solutionT(path, path.getLength());
}

void PsoPathSearch::sendPathTo(const Path & path, int host)const
{
  sizeT newBestPathSize = path.nodes.size();
  MPI_Send(&newBestPathSize, 1, MPI_UNSIGNED_LONG, host, 0, MPI_COMM_WORLD);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  //std::cout << "world_rank:"<<world_rank << " "<< "path size send:"<<newBestPathSize << std::endl;

  auto pathIndexes = graph.getNodeIndexesFromPath(path);
  MPI_Send(pathIndexes.data(), pathIndexes.size(), MPI_UNSIGNED_LONG,host,0,MPI_COMM_WORLD);
}

Path PsoPathSearch::receivePathFrom(int host)const
{
  sizeT newBestPathSize;
  MPI_Recv(&newBestPathSize, 1, MPI_UNSIGNED_LONG, host, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  //std::cout << "world_rank:"<<world_rank <<" "<< "path size received:"<<newBestPathSize << std::endl;

  auto newBestPathIndexes = std::vector<sizeT>(newBestPathSize);
  MPI_Recv(newBestPathIndexes.data(), newBestPathSize, MPI_UNSIGNED_LONG, host, 0, MPI_COMM_WORLD,MPI_STATUS_IGNORE);

  return graph.getPathFromNodeIndexes(newBestPathIndexes);
}

void PsoPathSearch::broadcastPathAs(const Path & path, int host)const
{
  sizeT newBestPathSize = path.nodes.size();
  MPI_Bcast(&newBestPathSize, 1, MPI_UNSIGNED_LONG, host, MPI_COMM_WORLD);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  //std::cout << "world_rank:"<<world_rank << " "<< "path size bcast:"<<newBestPathSize << std::endl;

  auto pathIndexes = graph.getNodeIndexesFromPath(path);
  MPI_Bcast(pathIndexes.data(), pathIndexes.size(), MPI_UNSIGNED_LONG,host,MPI_COMM_WORLD);
}
