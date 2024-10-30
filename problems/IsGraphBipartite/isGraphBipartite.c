# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct no {
    int dado;
    struct no *prox;
} No;
typedef struct {
    int v;
    int camada;
} vNo;
No *cria_fila(){
    No *fila = (No *) malloc(sizeof(No));
    if (fila != NULL){
        fila->dado = 0;
        fila->prox = NULL;
    }
    return fila;
}
void enfileira(No *fila, int dado){
    No *novo = (No *) malloc(sizeof(No));
    if (novo != NULL){
        novo->dado = dado;
        novo->prox = NULL;
        No *temp = fila;
        while (temp->prox != NULL) {
            temp = temp->prox;
        }
        temp->prox = novo;
    }
}
No *desenfileira(No *fila){
    if (fila->prox == NULL) {
        return NULL;
    }
    No *no = fila->prox;
    fila->prox = no->prox;
    return no;
}
int fila_vazia(No *fila){
    return (fila->prox == NULL);
}
int bfs(int **graph, int graphSize, No *fila, vNo *visited, int v){
    int camada = 0;
    visited[v].v = 1;
    visited[v].camada = camada;
    enfileira(fila, v);
    while(!fila_vazia(fila)){
        No *w = desenfileira(fila);
        camada++;
        v = w->dado;
        int vCamada = visited[v].camada;
        for (int i=0; i < graphSize; i++){
            if (graph[v][i] && visited[i].v == 0){
                visited[i].v = 1;
                visited[i].camada = camada;
                enfileira(fila, i);
            }
            else if (graph[v][i] && visited[i].v == 1){
                if (vCamada == visited[i].camada) return 0;
            }
        }
        free(w);
    }
    return 1;
}
bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    vNo *visited = (vNo *) malloc(graphSize * sizeof(vNo));
    for (int i=0; i < graphSize; i++){
        visited[i].v = 0;
        visited[i].camada = -1;
    }
    No *fila = cria_fila();
    int result = bfs(graph, graphSize, fila, visited, 0);
    free(fila);
    free(visited);
    return result == 1 ? true : false;
}