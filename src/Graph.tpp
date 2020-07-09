template <typename NID, typename N, typename E>
Graph<NID, N, E>::~Graph()
{
  auto it = nodes.begin();
  while (!nodes.empty())
  {
    delete (*it).second;
    it = nodes.erase(it);
  }
}

template <typename NID, typename N, typename E>
void Graph<NID, N, E>::print()
{
  for (auto& node : nodes)
  {
  std::cout<< "\nNode " << node.first << ": ";
  for (auto& edge : node.second->getEdges())
    std::cout << edge->nodes[1]->getId() << " ";
}
};

template <typename NID, typename N, typename E>
const NID Graph<NID, N, E>::addNode(NID id, N data, double x, double y)
{
  node* newnode = new node(id, data, x, y);
  nodes[id] = newnode;
  ++sizeOfGraph[0];

  return id;
};

template <typename NID, typename N, typename E>
bool Graph<NID, N, E>::addEdge(const int idN1, const int idN2, E weight)
{
  if (!nodes.count(idN1) || !nodes.count(idN2))
    return false; // not found

  // Get nodes
  node* n1=nodes[idN1];
  node* n2=nodes[idN2];

  bool inserted = n1->addEdge(n2, weight); // will also add edge to n2

  // Edge exists
  if (!inserted)
    return false;

  // Increase edge count
  ++sizeOfGraph[1];

  return true;
};

template <typename NID, typename N, typename E>
bool Graph<NID, N, E>::removeNode(const NID id)
{
  if (!nodes.count(id))
    return false; // not found

  node* n = nodes[id];

  // Remove node edges
  for (auto edge: n->edges)
    n->removeEdgeWith(edge->nodes[1]);
  delete n;

  // Remove from adjacency map
  nodes.erase(id);
  return true;
}

template <typename NID, typename N, typename E>
bool Graph<NID, N, E>::removeEdge(const NID idN1, const NID idN2)
{
  if (!nodes.count(idN1) || !nodes.count(idN2))
    return false; // not found
  
  // Get nodes
  node* n1=nodes[idN1];
  node* n2=nodes[idN2];

  return n1->removeEdgeWith(n2);
}