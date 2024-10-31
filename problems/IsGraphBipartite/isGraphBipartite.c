# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct no {
    int dado;
    struct no *prox;
} no;
typedef struct {
    int visitado;
    int camada;
} vNo;
no *cria_fila(){
    no *fila = (no *) malloc(sizeof(no));
    if (fila != NULL){
        fila->dado = 0;
        fila->prox = NULL;
    }
    return fila;
}
void enfileira(no *fila, int dado){
    no *novo = (no *) malloc(sizeof(no));
    if (novo != NULL){
        novo->dado = dado;
        novo->prox = NULL;
        no *temp = fila;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}
int desenfileira(no *fila){
    assert(!fila_vazia(fila));
    no *no = fila->prox;
    fila->prox = no->prox;
    int valor = no->dado;
    free(no);
    return valor;
}
int fila_vazia(no *fila){
    return (fila->prox == NULL);
}
int bfs(int **graph, int graphSize, int *graphColSize, no *fila, vNo *visited, int v){
    int camada = 0;
    visited[v].visitado = 1;
    visited[v].camada = camada;
    enfileira(fila, v);
    while(!fila_vazia(fila)){
        v = desenfileira(fila);
        camada++;
        int vCamada = visited[v].camada;
        for (int i=0; i < graphColSize[v]; i++){
            int vizinho = graph[v][i];
            if (visited[vizinho].visitado == 0){
                visited[vizinho].visitado = 1;
                visited[vizinho].camada = camada;
                enfileira(fila, vizinho);
            }
            else if (visited[vizinho].visitado == 1){
                if (vCamada == visited[vizinho].camada) return 0;
            }
        }
    }
    return 1;
}
bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    vNo *visited = (vNo *) malloc(graphSize * sizeof(vNo));
    for (int i=0; i < graphSize; i++){
        visited[i].visitado = 0;
        visited[i].camada = -1;
    }
    no *fila = cria_fila();
    for (int i=0; i<graphSize; i++){
        if (!visited[i].visitado){
            if (!bfs(graph, graphSize, graphColSize, fila, visited, i)){
                free(fila);
                free(visited);
                return false;
            }
        }
    }
    free(fila);
    free(visited);
    return true;
}