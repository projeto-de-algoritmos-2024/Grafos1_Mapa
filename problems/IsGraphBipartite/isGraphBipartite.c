# include <stdio.h>
# include <stdlib.h>

typedef struct no {
    int dado;
    int camada;
    struct no *prox;
} No;
No *cria_fila(){
    No *fila = (No *) malloc(sizeof(No));
    if (fila != NULL){
        fila->dado = 0;
        fila->prox = NULL;
    }
    return fila;
}
void enfileira(No *fila, int dado, int camada){
    No *novo = (No *) malloc(sizeof(No));
    if (novo != NULL){
        novo->dado = dado;
        novo->camada = camada;
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

int bfs(int **graph, int graphSize, No *fila, int *visited, int v){
    int camada = 0;
    visited[v] = 1;
    enfileira(fila, v, camada);
    while(!fila_vazia(fila)){
        No *w = desenfileira(fila);
        v = w->dado;
        int vCamada = w->camada;
        free(w);
        for (int i=0; i < graphSize; i++){
            if (graph[v][i] && visited[i] == 0){
                visited[i] = 1;
                enfileira(fila, i, vCamada+1);
            }
            if (graph[v][i] && visited[i] == 1){
                if (vCamada == camada) return 0;
            }
        }
        camada++;
    }
    return 1;
}

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int *visited = (int *) malloc(graphSize * sizeof(int));
    for (int i=0; i < graphSize; i++) visited[i] = 0;
    No *fila = cria_fila();
    int result = bfs(graph, graphSize, fila, visited, 0);
    free(fila);
    free(visited);
    return result;
}