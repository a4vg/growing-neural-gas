template <typename G, typename N, typename E>
Node<G, N, E>::~Node()
{
  while(!edges.empty())
  {
    delete this->edges.back();
    this->edges.pop_back();
  }
}

template <typename G, typename N, typename E>
void Node<G, N, E>::removeEdgeWith(Node *n2, bool removeOtherEnd)
{
  // Find edge and erase from edges
  auto& edgeIt = this->edges.begin();
  for (; edgeIt != this->edges.end(); ++edgeIt)
    if ((*edgeIt)->nodes[1] == n2)
      this->edges.erase(edgeIt);

  // Remove from other node edges
  if (removeOtherEnd)
  {
    n2->removeEdgeWith(this, false);
    delete *edgeIt;
  }
}

template <typename G, typename N, typename E>
bool Node<G, N, E>::addEdge(Node *n2, E weight, bool addOtherEnd)
{
  // Create edge
  edge* newEdge = new edge(this,n2,weight);

  // Find edge location in sorted vector
  auto itEdge = this->edges.begin();
  while (itEdge!=this->edges.end() && newEdge>*itEdge)
    ++itEdge;

  // Edge already in vector
  if (itEdge!=this->edges.end() && newEdge==*itEdge)
    return false;
  
  // Insert edge
  this->edges.insert(itEdge, newEdge);

  // Increase degree
  ++this->degree;

  if (addOtherEnd)
    n2->addEdge(this, weight, false);

  return true;
}  