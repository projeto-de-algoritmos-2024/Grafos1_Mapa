#include <stdio.h>
#include <stdlib.h>

void dfs(int **isConnected, int isConnectedSize, int *pai, int p, int v){
    pai[v] = p;
    for (int i=0; i < isConnectedSize; i++){
        if (isConnected[v][i] && pai[i] == -1){
            dfs(isConnected, isConnectedSize, pai, v, i);
        }
    }
}

int findCircleNum(int** isConnected, int isConnectedSize, int* isConnectedColSize) {
    int provincias = 0;
    int *pai = (int *) malloc(isConnectedSize * sizeof(int));
    for (int i=0; i < isConnectedSize; i++){
        pai[i] = -1;
    }
    for (int i=0; i < isConnectedSize; i++){
        if (pai[i] == -1){
            dfs(isConnected, isConnectedSize, pai, i, i);
            provincias++;
        }
    }
    return provincias;
}