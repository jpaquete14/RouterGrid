//Joao Paquete n89477//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct graph {
    int N;  //number of nodes//
    int** adj_matrix; //adjacency matrix//
} graph_t;


graph_t * create_graph( int N );
void add_edge( int i, int j, graph_t * g);

graph_t * create_graph( int N ) {
    int i, j;
    graph_t * g;
    g -> N = N;
    g->adj_matrix = (int **)malloc(N * sizeof( int *));
    for(i = 0; i<N; i++){
        g->adj_matrix[i] = (int *)malloc(N * sizeof(int));
    }
    for(i = 0; i < N; i++) {
        for(j = 0; j < N; j++) {
            g->adj_matrix[i][j] = 0;
        }
    }
    return g;
}

void add_edge( int i, int j, graph_t * g) {
    if( i > 0 && i < g->N && j > 0 && j < g->N && i != j ) {
        g->adj_matrix[i][j] = 1;
        g->adj_matrix[j][i] = 1;
    }
}

void delete_edge( int i, int j, graph_t * g) {
    if( i > 0 && i < g->N && j > 0 && j < g->N && i != j ) {
        g->adj_matrix[i][j] = 0;
        g->adj_matrix[j][i] = 0;
    }
}



int main() {
    int i, N, M, v1, v2;
    scanf("%d", &N);
    graph_t * g = create_graph(N);
    scanf("%d", &M);
    for( i = 0; i++; i<M ) {
        scanf("%d %d", &v1, &v2);
        add_edge( v1, v2, g);
    }
    
}

