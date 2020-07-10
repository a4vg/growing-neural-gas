#ifndef EDGE_H
#define EDGE_H

#include "Node.h"

template <typename G, typename N, typename E>
class Edge {
  public:
    typedef typename G::node node;
    node* nodes[2];
    E weight;

    Edge(node* n1,node* n2, E _weight):weight(_weight)
    {
      nodes[0]=n1;
      nodes[1]=n2;
    }
    ~Edge() { nodes[0] = nodes[1] = nullptr; }

    // Compare weights and, if equal, compare nodes
    bool operator==(Edge<G, N, E> cmp) { return nodes[0] == cmp.nodes[0] && nodes[1] == cmp.nodes[1]; }
    bool operator>(Edge<G, N, E> cmp) const { return cmp.weight==weight? nodes[1]>cmp.nodes[1] : weight>cmp.weight;}
    bool operator<(Edge<G, N, E> cmp) const { return cmp.weight==weight? nodes[1]<cmp.nodes[1] : weight<cmp.weight; }
};

#endif
