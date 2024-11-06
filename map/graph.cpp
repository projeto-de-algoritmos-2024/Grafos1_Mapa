#include "graph.h"

Graph::Graph(int n) : n(n), adj(n)
{
}

void Graph::addEdge(int u, int v)
{
    if (u < n && v < n && u >= 0 && v >= 0)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
}

const std::vector<int> &Graph::getAdjList(int node) const
{
    return adj[node];
}

int Graph::getSize() const
{
    return n;
}