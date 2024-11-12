#include <stdio.h>
#include <stdlib.h>

void dfs(int **isConnected, int isConnectedSize, int *visited, int v){
    visited[v] = 1;
    for (int i=0; i < isConnectedSize; i++){
        if (isConnected[v][i] && visited[i] == 0){
            dfs(isConnected, isConnectedSize, visited, i);
        }
    }
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) {
    int provinces = 0;
    int *visited = (int *) malloc(isConnectedSize * sizeof(int));
    for (int i=0; i < isConnectedSize; i++){
        visited[i] = 0;
    }
    for (int i=0; i < isConnectedSize; i++){
        if (visited[i] == 0){
            dfs(isConnected, isConnectedSize, visited, i);
            provinces++;
        }
    }
    return provinces;
}