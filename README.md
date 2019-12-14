# mobile_robot_computing
The project tests parallel and distributed computing. We implement them on Particle Swarm Optimization. The algorithm is used to choose optimum path.

## Budowanie programu algorytmu
W celu zbudowania projektu należy wywołać komendę:
```sh
g++  -g -fopenmp graphGenerator.cpp graph.cpp path.cpp psoPathSearch.cpp psoTests.cpp randomPath.cpp main.cpp
```
Utworzy ona plik wykonywalny ./o.out
Plik ten pzyjmuje następujące argumenty:
- bool inputFromFile - True oznacza, że graf zostanie pobrany z pliku
- int nr_of_iterators - liczba iteracji działania algorytmu
- int nr_of_threads - liczba wątków 
- int graphNrOfNodes - liczba węzłów grafu (wymagana gdy inputFromFile=False)
- double radiusOfNeighbourhood - kąt w zakresie jakiego w kierunku zmiany węzła wyszukiwany jest nowy (wymagana gdy inputFromFile=False)
- graph graph - graf z pliku (wymagana gdy inputFromFile=True)

## Testowanie działania algorytmu
Stworzono również plik benchmark.py. Można za jego pomocą uruchomić program wielokrotnie i sprawdzić efekt działania zrównoleglania obliczeń.
Zwraca on plik json z wynikami obliczeń i przyjętmi dla poszczególnych przypadków danymi wejściowymi.

## Przetwarzanie danych.
Dane statystyczne otrzymane z pliku benchmark.py sa przetwarzane z wykorzystaniem pliku aggregate_results.py