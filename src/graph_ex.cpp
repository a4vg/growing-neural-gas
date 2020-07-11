#include <iostream>
#include "Graph.h"

int main()
{
  Graph<int, int, int> g;

  g.addNode(1, 1, 10, 10);
  g.addNode(2, 2, 40, 10);
  g.addNode(3, 3, 40, 40);
  g.addNode(4, 4, 10, 40);
  g.addEdge(1, 2, 0);
  g.addEdge(2, 3, 0);
  g.addEdge(3, 4, 0);
  g.addEdge(4, 1, 0);
  g.addEdge(1, 3, 0);

  g.print();

  for (auto& n: g.knn(2, 50, 50))
      std::cout << n << "\n";
}