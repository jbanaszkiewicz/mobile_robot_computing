#include "psoTests.h"
#include "psoPathSearch.h"
#include "graph.h"
#include "graphGenerator.h"
#include <cassert>
#include <iostream>

PsoTests::PsoTests(/* args */)
{}

PsoTests::~PsoTests()
{}

void PsoTests::runTests()
{
  testGenerateGraph();
  testGetStart();
  testGetNeighbours();
  testGetNeighbourClosestTo();
  testUpdateParticle();
}

void PsoTests::testGenerateGraph()
{
  auto graph = GraphGenerator::getGraph(2, 2.0);
  assert(graph.getNodes().size() == 2);
  assert(graph.edges.size() == 2);
}

void PsoTests::testGetStart()
{
  auto graph = GraphGenerator::getGraph(2, 2.0);
  assert( GraphGenerator::getStart(graph).position == pointT(0, 0) );
  assert( &(GraphGenerator::getStart(graph)) == &(graph.nodes[0]));
}

void PsoTests::testGetNeighbours()
{
  auto graph = GraphGenerator::getGraph(2, 2.0);
  auto neighbours = graph.getNeighbours(&(GraphGenerator::getStart(graph)));

  assert( std::distance(neighbours.first,neighbours.second) == 1);

  auto i =  neighbours.first;
  
  assert( i->first->position == pointT(0, 0));
  assert( i->second.first->position == pointT(1, 1));
  
}

void PsoTests::testGetNeighbourClosestTo()
{
  auto graph = GraphGenerator::getGraph(3, 2.0);
  auto search = PsoPathSearch(graph,GraphGenerator::getStart(graph),GraphGenerator::getDestination(graph));

  auto neighbours = graph.getNeighbours(&GraphGenerator::getStart(graph));
  auto closest = search.getNeighbourClosestTo(neighbours, 
    &GraphGenerator::getDestination(graph),
    &GraphGenerator::getDestination(graph));

  assert(closest == &GraphGenerator::getDestination(graph));
}

void PsoTests::testUpdateParticle()
{
  auto graph = GraphGenerator::getGraph(3, 2.0);
  auto search = PsoPathSearch(graph,GraphGenerator::getStart(graph),GraphGenerator::getDestination(graph));
  
  auto particle = Particle();
  auto particlePath = Path();
  auto bestPath = Path();
  
  auto particleNodes = std::vector<const Node*>();
  particleNodes.push_back(&GraphGenerator::getStart(graph));
  particleNodes.push_back(&graph.nodes[2]);
  particleNodes.push_back(&GraphGenerator::getDestination(graph));
  particlePath.nodes = particleNodes;
  particle.bestPath = particlePath;
  particle.currentPath = particlePath;

  auto bestSolutionNodes = std::vector<const Node*>();
  bestSolutionNodes.push_back(&GraphGenerator::getStart(graph));
  bestSolutionNodes.push_back(&GraphGenerator::getDestination(graph));
  bestPath.nodes = bestSolutionNodes;
  auto bestSolution = std::pair<Path,costT>(bestPath, 0);
  
  search.updateParticle(particle, bestSolution);

  assert(particle.currentPath.nodes == bestPath.nodes);
}