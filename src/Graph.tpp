template <typename N, typename E>
Graph<N, E>::~Graph()
{
  auto it = nodes.begin();
  while (!nodes.empty())
  {
    delete (*it).second;
    it = nodes.erase(it);
  }
}

template <typename N, typename E>
void Graph<N, E>::print()
{
  for (auto& node : nodes)
  {
  std::cout<< "\nNode " << node.first << ": ";
  for (auto& edge : node.second->getEdges())
    std::cout << edge->nodes[1]->getData() << " ";
}
};

template <typename N, typename E>
bool Graph<N, E>::addNode(N nodeName, double x, double y)
{
  if (nodes.find(nodeName)!=nodes.end()) return false; // name taken

  node* newnode = new node(nodeName, x, y);
  nodes[nodeName] = newnode;
  ++sizeOfGraph[0];

  return true;
};

template <typename N, typename E>
bool Graph<N, E>::addEdge(N n1Data, N n2Data, E weight)
{
  if (!nodes.count(n1Data) || !nodes.count(n2Data))
    return false; // not found

  // Get nodes
  node* n1=nodes[n1Data];
  node* n2=nodes[n2Data];

  bool inserted = n1->addEdge(n2, weight); // will also add edge to n2

  // Edge exists
  if (!inserted)
    return false;

  // Increase edge count
  ++sizeOfGraph[1];

  return true;
};

template <typename N, typename E>
bool Graph<N, E>::removeNode(N nData){
  if (nodes.find(nData)==nodes.end())
    return false; // not found

  node* n = nodes[nData];

  // Remove node edges
  for (auto edge: n->edges)
    n->removeEdgeWith(edge->nodes[1]->data);
  delete n;

  // Remove from adjacency map
  nodes.erase(nData);
  return true;
}

template <typename N, typename E>
bool Graph<N, E>::removeEdge(N n1Data, N n2Data){
  if (nodes.find(n1Data)==nodes.end())
    return false; // not found

  return nodes[n1Data]->removeEdgeWith(n2Data);
}