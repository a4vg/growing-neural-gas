#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <list>
#include <map>

#include "Node.h"
#include "Edge.h"

int const INFINITE=INT16_MAX;

template <typename N, typename E>
class Graph {
  public:
    typedef Graph<N, E> self;
    typedef Node<self, N, E> node;
    typedef Edge<self, N, E> edge;
    typedef std::map<N, node*> NodeSeq;
    typedef std::list<node*> NodeList;
    typedef std::vector<edge*> EdgeSeq;
    typedef typename NodeSeq::iterator NodeIte;
    typedef typename EdgeSeq::iterator EdgeIte;

  private:
    NodeSeq nodes; // adjacency map <data (node data), node pointer>
    int sizeOfGraph[2]= {0,0}; // {n nodes, n edges}

  public:
    Graph(){};
    ~Graph();

    void print();
    int* size(){ return sizeOfGraph; };

    // Insertions and deletions
    bool addNode(N nodeName, double x=0, double y=0);
    bool addEdge(N n1Data, N n2Data, E weight);
    bool removeNode(N nData);
    bool removeEdge(N n1Data, N n2Data);
};

#include "Graph.tpp"

#endif