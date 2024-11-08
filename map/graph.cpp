#include "graph.h"
#include <vector>
#include <algorithm>
#include <queue>
#include <iostream>

Graph::Graph(int n) : n(n), adj(n)
{
}

Graph::Graph(const std::vector<std::vector<int>> &adj) : adj(adj), n(adj.size())
{
}

Graph::~Graph() = default;
void Graph::addEdge(int u, int v)
{
    if (u < n && v < n && u >= 0 && v >= 0)
    {
        adj[u].push_back(v);
    }
}

const std::vector<int> &Graph::getAdjListFromNode(int node) const
{
    return adj[node];
}

const std::vector<std::vector<int>> &Graph::getAdjList() const
{
    return adj;
}


int Graph::getSize() const
{
    return n;
}

void Graph::dfs(int node, std::vector<bool> &visited, std::vector<int> &ans) const
{
    visited[node] = true;
    for (int neighbor : adj[node])
    {
        if (!visited[neighbor])
            dfs(neighbor, visited, ans);
    }
    ans.push_back(node);
}

std::vector<int> Graph::topologicalSort() const
{
    if (!adj.size()) {
        std::cerr << "Adjacency list is empty!" << std::endl;
        return {};
    }
    
    std::vector<bool> visited(n, false);
    std::vector<int> ans;

    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
            dfs(i, visited, ans);
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

void Graph::printGraph(std::vector<std::vector<int>> &adj) const
{
    for (int i = 0; i < n; ++i) {
        std::cout << i << ": ";
        for (int neighbor : adj[i]) {
            std::cout << neighbor << " ";
        }
        std::cout << std::endl;
    }
}

void Graph::printTopologicalSort(std::vector<int> &top_order) const {
    for (int node : top_order) {
        std::cout << node << " ";
    }
    std::cout << std::endl;
}

Graph Graph::removeNodes(std::vector<int> selected_nodes) const {
    std::vector<std::vector<int>> new_adj = adj; // Copia a lista de adjacência original

    // Marcar os nós a serem removidos
    std::vector<bool> to_remove(n, false);
    for (int node : selected_nodes)
    {
        to_remove[node] = true;
    }

    // Criar uma nova lista de adjacência apenas com os nós restantes
    std::vector<std::vector<int>> remaining_adj(n);

    for (int i = 0; i < n; ++i)
    {
        if (!to_remove[i])
        { // Se o nó não estiver na lista de remoção
            for (int neighbor : adj[i])
            {
                if (!to_remove[neighbor])
                { // Só adiciona vizinhos que também não serão removidos
                    remaining_adj[i].push_back(neighbor);
                }
            }
        }
    }

    return Graph(remaining_adj);
}