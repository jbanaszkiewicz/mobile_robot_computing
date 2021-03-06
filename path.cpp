#include "path.h"
#include <cmath>

Path::Path()
{
}

Path::~Path()
{
}

// Zwraca i-ty węzeł ze ścieżki
// Jeżeli ścieżka nie ma i węzłów
//   to zwraca ostani
const Node* Path::getNode(size_t i)const
{
  if(i >=  nodes.size())
  {
    return nodes.back();
  }
  return nodes[i];
}

// Zwraca dlugość scieżki, oblicza odległości między węzłami
// mogło by być odrobinę szybsze gdyby zastosować
// wektor map jako kontener na krawędzie
realT Path::getLength()const
{
  realT length = 0;
  realT partialLength = 0;

  realT previousX = this->nodes.at(0)->getPositionX();
  realT previousY = this->nodes.at(0)->getPositionY();
  realT currentX, currentY;

  for (auto i = 1; i < this->nodes.size(); i++)
  {
    currentX = this->nodes.at(i)->getPositionX();
    currentY = this->nodes.at(i)->getPositionY();

    partialLength = sqrt( pow( currentX - previousX, 2 ) + pow( currentY - previousY, 2 ) );
    length += partialLength;

    if (i != (this->nodes.size() - 1))
    {
      previousX = currentX;
      previousY = currentY;
    }
  }

  return length;
}

// Dodawanie podanego węzła na koniec ścieżki
void Path::addNodeToPath(const Node* node)
{
  this->nodes.push_back(node);
}