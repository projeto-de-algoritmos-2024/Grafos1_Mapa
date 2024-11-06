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

private:
    std::vector<std::vector<int>> adj;
    int n;
};

#endif