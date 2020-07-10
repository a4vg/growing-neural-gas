#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <map>

#include "Node.h"
#include "Edge.h"

template <typename NID, typename N, typename E>
class Graph
{
  public:
    typedef Graph<NID, N, E> self;
    typedef Node<self, NID, N, E> node;
    typedef Edge<self, N, E> edge;
    typedef std::map<NID, node*> NodeSeq;
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
    const NID addNode(NID id, N data, double x, double y);
    bool addEdge(const int idN1, const int idN2, E weight);
    bool removeNode(const NID id);
    bool removeEdge(const NID idN1, const NID idN2);
    NodeIte removeNode(node* n);
    EdgeIte removeEdge(node* n1, node* n2);

    // Access methods
    node* getNode(const NID id);
    edge* getEdge(const NID idN1, const NID idN2);

    // Iterator
    NodeIte begin() { return nodes.begin();}
    NodeIte end() { return nodes.end();}
};

#include "Graph.tpp"

#endif