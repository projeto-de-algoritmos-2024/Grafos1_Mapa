// Geek for Geeks: Level of Nodes
// Difficulty: Medium
// https://www.geeksforgeeks.org/problems/level-of-nodes-1587115620/1

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution
{
public:
    void addEdge(vector<int> adj[], int u, int v)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Function to find the level of node X.
    int nodeLevel(int V, vector<int> adj[], int X)
    {
        queue<int> q;
        bool visited[V] = {false};
        int first_node = 0;

        visited[first_node] = true;
        q.push(first_node);

        int level = 0;
        q.push(-1); // Delimita a troca de nível na bfs

        while (!q.empty())
        {
            int curr = q.front();
            q.pop();

            if (curr == -1)
            {
                level++;
                if (!q.empty())
                    q.push(-1); // Adiciona outro delimitador caso ainda haja elementos na fila
                continue;
            }

            if (curr == X)
            {
                return level;
            }

            for (int x : adj[curr])
            {
                if (!visited[x])
                {
                    visited[x] = true;
                    q.push(x);
                }
            }
        }
        return -1;
    }
};

int main()
{
    Solution s;

    vector<int> adj[6];
    s.addEdge(adj, 0, 1);
    s.addEdge(adj, 0, 2);
    s.addEdge(adj, 1, 3);
    s.addEdge(adj, 1, 4);
    s.addEdge(adj, 2, 5);

    cout << s.nodeLevel(6, adj, 4) << "\n";

    vector<int> adj2[4];
    s.addEdge(adj2, 0, 1);
    s.addEdge(adj2, 0, 2);
    s.addEdge(adj2, 0, 3);

    cout << s.nodeLevel(4, adj2, 1) << "\n";

    return 0;
}