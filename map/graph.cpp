#include "graph.h"
#include <vector>
#include <algorithm>
#include <queue>

Graph::Graph(int n) : n(n), adj(n)
{
}

void Graph::addEdge(int u, int v)
{
    if (u < n && v < n && u >= 0 && v >= 0)
    {
        adj[u].push_back(v);
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

void Graph::dfs(int node, std::vector<bool> &visited, std::vector<int> &ans, const std::vector<std::vector<int>> &adj) const
{
    visited[node] = true;
    for (int neighbor : adj[node])
    {
        if (!visited[neighbor])
            dfs(neighbor, visited, ans, adj);
    }
    ans.push_back(node);
}

std::vector<int> Graph::topologicalSort(int n, std::vector<std::vector<int>> &adj) const
{
    std::vector<bool> visited(n, false);
    std::vector<int> ans;

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
            dfs(i, visited, ans, adj);
    }

    std::reverse(ans.begin(), ans.end());
    return ans;
}

std::vector<int> Graph::kahn(int n, std::vector<std::vector<int>> &adj) const
{
    std::vector<int> inDegree(n, 0); // Grau de entrada, ou seja, número de arestas que chegam no vértice

    for (int i = 0; i < n; ++i)
        for (int neighbor : adj[i]) inDegree[neighbor]++; // Incrementa o grau de entrada do vizinho

    std::queue<int> q;

    for (int i = 0; i < n; ++i) 
        if (inDegree[i] == 0) q.push(i); // Se o grau de entrada for 0 significa que o vértice pode ser imediatamente processado

    std::vector<int> ans;

    while (!q.empty()) {
        int node = q.front(); q.pop();
        ans.push_back(node);

        for (int neighbor : adj[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) q.push(neighbor);
        }
    }

    return ans;

}   