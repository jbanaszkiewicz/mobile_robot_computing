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

// Funkcja FindShortestPath:
// 1. Generuje cząstki z losowymi ścieżkami
// 2. Zapisuje najlepsze rozwiązanie
// 3. maximumIterations razy
//   3.a Poprawia ścieżkę każdej cząstki w oparciu o najlepszą dla niej i najlepszą globalnie
//   3.b Zapisuje dotychczasowe najlepsze rozwiązanie
std::pair<Path,costT> PsoPathSearch::FindShortestPath(
  sizeT numberOfParticles, sizeT maximumIterations = 500)
{ 
  std::vector<Particle> particles = getParticles( numberOfParticles );
  const auto firstParticle = particles.front();
  const auto anySolution = std::pair<Path,costT>(firstParticle.currentPath, firstParticle.currentCost);
  std::pair<Path,costT> bestSolution = getBestSolution(particles,anySolution ); // g, gBest

  maxPathLenght = getMaxPathLenght(particles);

  for(sizeT i = 0; i < maximumIterations; ++i)
  {
    particles = updateParticles(particles, bestSolution);
    bestSolution = getBestSolution(particles,bestSolution);
  }

  return bestSolution;
}

// Funkcja getParticles:
// 1. Generuje losowe ścieżki
// 2. Dla każdej ścieżki
//   2.a Obliczana jest jej długośc
//   2.b Tworzona jest na podstawie ścieżki cząstka
std::vector<Particle> PsoPathSearch::getParticles(
  sizeT numberOfParticles )const
{
  auto randomPaths = RandomPath::getRandomPaths(graph, numberOfParticles, start, destination);
  auto particles = std::vector<Particle>(numberOfParticles);
  
  #pragma omp parallel for
  for (sizeT i = 0; i < numberOfParticles; i++)
  {
    auto pathLength = randomPaths[i].getLength();
    particles[i] = Particle(randomPaths[i],pathLength);
  }
  return particles;
}

// Funkcja getBestSolution:
// Spośród ścieżek przechowywanych przez cząstki i najlepszej ścieżki dotychczas wybierana jest nowa najlepsza
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

// Funkcja getMaxPathLength:
// Obliczanie maxymalnej liczby węzłów w ścieżkach
// Słóży do ograniczenia długości ścieżki
sizeT PsoPathSearch::getMaxPathLenght(const std::vector<Particle>& particles) const
{
  auto particleWithLongestPath =  std::max_element(particles.begin(),particles.end(),
    [](Particle l, Particle r) { 
      return l.currentPath.nodes.size() < r.currentPath.nodes.size(); 
  });
  return particleWithLongestPath->currentPath.nodes.size();
}

// Funkcja updateParticles:
// 1. Dla każdej cząsteczki
//   1.a Wylicza nową ścieżkę
//   1.b Aktualizuje ścieżkę w cząsteczce
std::vector<Particle> PsoPathSearch::updateParticles(
  std::vector<Particle>& particles,const std::pair<Path,costT>& bestSolution)const
{
  #pragma omp parallel for
  for(size_t i = 0; i < particles.size();++i)
  {
    const auto newPath = getNextPath(particles[i],bestSolution);
    particles[i].setPath(newPath);
  } 
  return particles;
}

// Funkcja getNextPath:
// Tworzy nową ścieśkę rozpoczynając od startu
// W każdym kroku dodaje węzeł króry jest najbliżej i-tego węzła ścieżki najlepszej dla cząsteczki i najlepszej globalnie
// Jeżeli utworzona zostanie ścieżka dłuższa niż najdłuższa ścieżka losowa
//   to zwraca pierwotną ścieżkę cząsteczki
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

// Funkcja getNeighbourClosestTo:
// Znajduje sąsiada dla którego suma odległości od podanych węzów jest najmniejsza
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

// Funkcja setPath:
// Aktualizuje cząsteczkę w oparciu o nową ścieżkę
// Jeżeli nowa ścieżka jest krótsza od najlepszej dotychczas dla danej cząsteczki
//   to nowa ścieżka staje się najlepsza dotychczas
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