#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

typedef struct Vertex {
    int index;
    std::string discipline;
} Vertex;

class Graph
{
public:
    std::vector<std::vector<std::string>> disciplines;

    explicit Graph(int n);
    ~Graph();

    Graph(const std::vector<std::vector<int>> &adj, const std::vector<std::vector<std::string>> &disciplines);

    void addEdge(int u, int v);

    const std::vector<int> &getAdjListFromNode(int node) const;

    const std::vector<std::vector<int>> &getAdjList() const;

    int getSize() const;

    void dfs(int node, std::vector<bool> &visited, std::vector<int> &ans) const;

    std::vector<int> topologicalSort() const; // DFS based

    std::vector<int> kahn(int n, std::vector<std::vector<int>> &adj) const; // BFS based

    void printGraph(std::vector<std::vector<int>> &adj) const;

    void printTopologicalSort(std::vector<int> &top_order) const;

    Graph* removeNodes(std::vector<int> selected_nodes) const;

private:
    std::vector<std::vector<int>> adj;
    int n;
};

#endif