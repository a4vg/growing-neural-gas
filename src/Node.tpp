template <typename G, typename NID, typename N, typename E>
Node<G, NID, N, E>::~Node()
{
  while(!edges.empty())
  {
    delete this->edges.back();
    this->edges.pop_back();
  }
}

template <typename G, typename NID, typename N, typename E>
typename Node<G, NID, N, E>::EdgeIte Node<G, NID, N, E>::removeEdgeWith(Node *n1, Node *n2, bool removeOtherEnd)
{
  // Find edge and erase from edges
  auto it = this->edges.begin();
  for (; it != this->edges.end(); ++it)
    if ((*it)->nodes[1] == n2)
    {
      delete *it;
      it = this->edges.erase(it);
      break;
    }

  // Remove from other node edges
  if (removeOtherEnd)
    n2->removeEdgeWith(n2, n1, false);

  return it;
}

template <typename G, typename NID, typename N, typename E>
bool Node<G, NID, N, E>::addEdge(Node *n1, Node *n2, E &weight, bool addOtherEnd)
{
  // Create edge
  edge* newEdge = new edge(n1,n2,weight);

  // Insert edge
  // std::cout << "Adding edge connecting " << this->getId() << " and " << n2->getId() << "\n";

  // Edge already in vector
  for (auto& e: this->edges)
  {
    if (e->nodes[1] == n2)
      return false;
  }

  this->edges.push_back(newEdge);

  if (addOtherEnd)
    n2->addEdge(n2, n1, weight, false);

  return true;
}  