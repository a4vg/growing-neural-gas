#ifndef NODE_H
#define NODE_H

template <typename G, typename NID, typename N, typename E>
class Node {
  public:
    typedef typename G::edge edge;
    typedef typename G::EdgeSeq EdgeSeq;

  private:
    const NID id;
    N data;
    EdgeSeq edges;

  public:
    double x;
    double y;
    int degree=0;
    
    Node(NID _id, N _data=N{}, double _x=0, double _y=0) : id(_id), data(_data), x(_x), y(_y){};
    ~Node();

    void removeEdgeWith(Node *n2, bool removeOtherEnd = true);
    bool addEdge(Node *n2, E &weight, bool addOtherEnd = true);

    EdgeSeq getEdges(){ return edges; };
    N getData(){ return data; }
    const NID getId(){ return id; }
    bool alone(){ return !degree; } // no edges connected
};

#include "Node.tpp"

#endif