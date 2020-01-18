#ifndef PATH_H
#define PATH_H
#include <vector>
#include "graph.h"
class Node;

// Klasa reprezentująca ścieżkę
class Path
{
public:
  // Węzły znajdujące się na ścieżce
  std::vector<const Node*> nodes;

  // Konstruktor
  Path();
  // Destruktor
  ~Path();
  // Pobranie i-tego węzła ze ścieżki
  const Node* getNode(size_t i)const;
  // Funkcja zwracająca długość ścieżki
  realT getLength()const;
  // Dodawanie węzła do ścieżki
  void addNodeToPath(const Node* node);
};

#endif // PATH_H