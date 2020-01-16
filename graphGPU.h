#ifndef GraphGPU_H
#define GraphGPU_H
#include <stddef.h> // size_t
#include <vector> // to del use ecuda
#include <utility>  /* pair */
#include <cuda_runtime_api.h>
#include <cuda.h>
#include <ecuda/ecuda.hpp>
#include "graph.h"

class NodeGPU;
class PathGPU;

using sizeT = size_t;
using realT = double;
using edgeT = ecuda::pair<sizeT,realT>; // (index in nodes, distance)
using edgesT = ecuda::vector<ecuda::vector<edgeT>>; // lista sąsiedztw (wektor[węzeł_na_początku_krawędzi] = wektorów[(węzeł_na_końcu,długość)]) 

class NodeGPU
{
public:
  ecuda::pair<realT, realT> position;

  NodeGPU(std::pair<realT, realT> p)
  {
    position = ecuda::pair<realT, realT>(p.first,p.second);
  }
  // ASK TOMEK? tutaj brakuje bool operator'ow // dopisać tylko potrzebne
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
  ecuda::vector<NodeGPU> nodes;
  edgesT edges;
  
public:
  GraphGPU(Graph g);
  ~GraphGPU();
  __device__  
  ecuda::vector<NodeGPU> getNodes()const;
  __device__  // ta funkcja jest trudna, przejrzeć jej użycia, najlepiej zamienić na getNeighboursVector
  std::pair<edgesT::const_iterator,edgesT::const_iterator>
    getNeighbours(const NodeGPU* node)const;
  __device__  
  ecuda::vector< edgeT> getNeighboursVector(
      const sizeT node);    
};
// PYT tutaj jest duzo mniej funkcji zadeklarowanych niz w oryginalnym pliku graph.h
#endif //GraphGPU_H