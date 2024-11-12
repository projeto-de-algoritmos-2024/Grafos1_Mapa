#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

class Graph
{
public:
    explicit Graph(int n);
    ~Graph();

    void addEdge(int u, int v);
    const std::vector<int>& getAdjList(int node) const;
    int getSize() const;
    void dfs(int node, std::vector<bool> &visited, std::vector<int> &ans, const std::vector<std::vector<int>>& adj) const;
    std::vector<int> topologicalSort(int n, std::vector<std::vector<int>> &adj) const; //DFS based
    std::vector<int> kahn(int n, std::vector<std::vector<int>> &adj) const; // BFS based

private:
    std::vector<std::vector<int>> adj;
    int n;
};

#endif