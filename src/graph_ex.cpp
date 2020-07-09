#include <iostream>
#include "Graph.h"

int main()
{
  Graph<int, int, int> g;

  g.addNode(1, 1, 0, 0);
  g.addNode(2, 2, 1, 2);
  g.addNode(3, 3, 1, 0);
  g.addNode(4, 4, 1, -2);
  g.addNode(5, 5, 3, 2);
  g.addNode(6, 6, 3, 0);
  g.addNode(7, 7, 3, -2);
  g.addNode(8, 8, 5, -2);
  g.addNode(9, 9, 5, 0);

  g.addEdge(1, 2, 5);
  g.addEdge(1, 3, 25);
  g.addEdge(2, 5, 11);
  g.addEdge(2, 6, 33);
  g.addEdge(3, 4, 17);
  g.addEdge(3, 6, 38);
  g.addEdge(4, 7, 12);
  g.addEdge(5, 6, 21);
  g.addEdge(5, 9, 1);
  g.addEdge(6, 4, 4);
  g.addEdge(6, 7, 3);
  g.addEdge(7, 8, 50);
  g.addEdge(8, 6, 41);
  g.addEdge(9, 6, 2);
  g.addEdge(9, 8, 14);

  g.print();
}