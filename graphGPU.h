#ifndef GraphGPU_H
#define GraphGPU_H
#include <stddef.h> // size_t
#include <vector> // to del use ecuda
#include <utility>  /* pair */
#include <map>
#include <ecuda/ecuda.hpp>
#include "graph.h"

class Node;
class Path;

using sizeT = size_t;
using realT = double;
using valueT = ecuda::pair<const Node*,realT>;
// using mapT = std::multimap<keyT,valueT>;
// numer węzła - index w zewnętrznym wektorze
// sąsiad i odległość - elementy 2 wektora  
using mapT = ecuda::vector<ecuda::vector<valueT>>;

class NodeGPU
{
public:
  ecuda::pair<realT, realT> position;


  NodeGPU(std::pair<realT, realT> p)
  {
    position =   ecuda::pair<realT, realT>(p.first,p.second);
  }
  
  __device__
  realT getPositionX()const;
  __device__
  realT getPositionY()const;
  __device__
  void setPositionX(realT x);
  __device__  
  void setPositionY(realT y);
};

class GraphGPU
{
private:
  std::vector<Node> nodes;
  mapT edges;
  
public:
  GraphGPU(Graph g);
  ~GraphGPU();
  __device__  
  const std::vector<Node>& getNodes()const;
  __device__  
  std::pair<mapT::const_iterator,mapT::const_iterator>
    getNeighbours(const Node* node)const;
  __device__  
  ecuda::vector< valueT> getNeighboursVector(
      const sizeT node)const;    
};

#endif //GraphGPU_H