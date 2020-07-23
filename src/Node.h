#ifndef NODE_H
#define NODE_H

template <typename G, typename NID, typename N, typename E>
class Node {
  public:
    typedef typename G::edge edge;
    typedef typename G::EdgeSeq EdgeSeq;
    typedef typename G::EdgeIte EdgeIte;
    typedef typename G::NodeIte NodeIte;

  private:
    const NID id;
    EdgeSeq edges;

  public:
    float x;
    float y;
    N data;
    
    Node(NID _id, N _data=N{}, float _x=0, float _y=0) : id(_id), data(_data), x(_x), y(_y){};
    ~Node();

    EdgeIte removeEdgeWith(Node *n1, Node *n2, bool removeOtherEnd = true);
    bool addEdge(Node *n1, Node *n2, E &weight, bool addOtherEnd = true);

    EdgeSeq getEdges(){ return edges; };
    const NID getId(){ return id; };
    void move(float _x, float _y){ x=_x; y=_y; };

    bool alone(){ return edges.empty(); }; // no edges connected
    float distance(float x, float y){ return G::distance(this->x, this->y, x, y); };
};

#include "Node.tpp"

#endif