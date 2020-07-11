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
typename Graph<NID, N, E>::NodeIte Graph<NID, N, E>::removeNode(node* n)
{
  // Remove node edges
  for (auto edge: n->edges)
    n->removeEdgeWith(edge->nodes[1]);
  delete n;

  // Decrease node count
  --sizeOfGraph[0];

  // Remove from adjacency map
  return nodes.erase(n->getId());
}

template <typename NID, typename N, typename E>
bool Graph<NID, N, E>::removeNode(const NID id)
{
  if (!nodes.count(id))
    return false; // not found

  node* n = nodes[id];
  removeNode(n);

  return true;
}

template <typename NID, typename N, typename E>
typename Graph<NID, N, E>::EdgeIte Graph<NID, N, E>::removeEdge(node* n1, node* n2)
{
  // Decrease edge count
  --sizeOfGraph[1];

  return n1->removeEdgeWith(n2);
}

template <typename NID, typename N, typename E>
bool Graph<NID, N, E>::removeEdge(const NID idN1, const NID idN2)
{
  if (!nodes.count(idN1) || !nodes.count(idN2))
    return false; // not found
  
  // Get nodes
  node* n1=nodes[idN1];
  node* n2=nodes[idN2];
  removeEdge(n1, n2);

  return true;
}

template <typename NID, typename N, typename E>
typename Graph<NID, N, E>::node* Graph<NID, N, E>::getNode(const NID id)
{
  if (!nodes.count())
    return nullptr; // not found

  return nodes[id];
}

template <typename NID, typename N, typename E>
typename Graph<NID, N, E>::edge* Graph<NID, N, E>::getEdge(const NID idN1, const NID idN2)
{
  if (!nodes.count(idN1) || !nodes.count(idN2))
    return nullptr; // not found

  for (auto& edge: nodes[idN1]->getEdges())
    if (edge->nodes[1]->getId() == idN2)
      return edge;
}

template <typename NID, typename N, typename E>
float Graph<NID, N, E>::distance(float x1, float y1, float x2, float y2)
{
  return std::sqrt(std::pow(x1-x2, 2) + std::pow(y1-y2, 2));
}

template <typename NID, typename N, typename E>
std::vector<NID> Graph<NID, N, E>::knn(int n, float x, float y)
{
  // Separate nodes id
  std::vector<NID> neighborsId;
  for (auto& node : nodes)
    neighborsId.push_back(node.first);

  // Make sure n is not larger than the number of nodes
  n = n>neighborsId.size()? neighborsId.size(): n;

  // Sort nodes id by distance, but only rearranges the first n elements
  std::partial_sort(neighborsId.begin(), neighborsId.begin() + n, neighborsId.end(),
    [this, x, y](NID idN1, NID idN2)
    {
      float dist1 = Graph<NID, N, E>::distance(x, y, this->nodes[idN1]->x, this->nodes[idN1]->y);
      float dist2 = Graph<NID, N, E>::distance(x, y, this->nodes[idN2]->x, this->nodes[idN2]->y);
      return dist1 < dist2;
    });

  // Return the first n elements
  neighborsId.resize(n);
  return neighborsId;

}