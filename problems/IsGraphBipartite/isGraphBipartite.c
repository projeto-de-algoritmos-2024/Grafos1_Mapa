# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>

typedef struct no {
    int dado;
    struct no *prox;
} no;
typedef enum cor {
    UNVISITED = 0,
    BLUE = 1,
    RED = 2,
} cor;

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
int bfs(int **graph, int graphSize, int *graphColSize, no *fila, cor *cores, int v){
    cores[v] = BLUE;
    enfileira(fila, v);
    while(!fila_vazia(fila)){
        v = desenfileira(fila);
        for (int i=0; i < graphColSize[v]; i++){
            int vizinho = graph[v][i];
            if (cores[vizinho] == UNVISITED){
                cores[vizinho] = (cores[v] == BLUE) ? RED : BLUE;
                enfileira(fila, vizinho);
            }
            if (cores[v] == cores[vizinho]){
                    return 0;
            }
        }
    }
    return 1;
}
bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    cor *cores = (cor *) malloc(graphSize * sizeof(cor));
    for (int i=0; i < graphSize; i++){
        cores[i] = UNVISITED;
    }
    no *fila = cria_fila();
    for (int i=0; i<graphSize; i++){
        if (cores[i] == UNVISITED){
            if (!bfs(graph, graphSize, graphColSize, fila, cores, i)){
                free(fila);
                free(cores);
                return false;
            }
        }
    }
    free(fila);
    free(cores);
    return true;
}