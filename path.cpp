#include "path.h"

Path::Path(/* args */)
{
}

Path::~Path()
{
}

const Node* Path::getNode(size_t i)const
{
  if(i >=  nodes.size())
  {
    return nodes.back();
  }
  return nodes[i];
}

realT Path::getLength()const
{
  //TODO: ADAM napisac kod pod dlugosc sciezki

  // PSEUDOKOD: weź pierwszy element wektora
  // zapisz jego współrzędne jako współrzędne węzła poprzedniego
  // sumuj odległości w pętli aż do wyrazu n
  // pamiętaj współrzędne węzła poprzedniego i aktualizuj

  // zwróć długość ścieżki - to dosyć prosta funkcja będzie

  throw std::logic_error("getPathLength Not Implemented");
  return realT();
}

void Path::addNodeToPath(const Node* node)
{
  this->nodes.push_back(node);
}