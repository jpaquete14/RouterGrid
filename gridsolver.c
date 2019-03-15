//Joao Paquete n89477//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct graph {
    int N, M;  //number of nodes//
    int** adj_matrix; //adjacency matrix//
} graph_t;


typedef struct node {
    int value;
    struct node * next; 
} node_t;

graph_t * create_graph( int N);
void add_edge( int i, int j, graph_t * g);
void delete_edge( int i, int j, graph_t * g);
void print_graph( graph_t * g);
void free_graph( graph_t * g);

node_t * create_stack();
void push(int n, node_t * top);
int pop( node_t * top);


/*=======================================================
 *Stack functions
 *=======================================================
 */
node_t * create_stack() {
    node_t * s = NULL;
    return s;
}

void push(int n, node_t * top) {
    node_t * new;
    new = (node_t *) malloc(sizeof(struct node));
    new->value = n;
    new->next = top;
    top = new; 
}


int pop( node_t * top) {
    int value;   
    node_t * old;   
    if (top != NULL) {     
        value = top->value;     
        old = top;     
        top = top->next;     
        free(old);     
        return value;  
    }   
    else return -1; 
}

/* =============================================================================
 * graph functions
 * =============================================================================
 */
graph_t * create_graph( int N ) {
    int i, j;
    graph_t * g = (graph_t *)malloc(sizeof(graph_t));
    g -> N = N;
    g -> M = 0;     //Starts with 0 edges//
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
    if( i > 0 && i <= g->N && j > 0 && j <= g->N && i != j ) {
        i = i-1;
        j = j-1;
        g->adj_matrix[i][j] = 1;
        g->adj_matrix[j][i] = 1;
    }
}

void delete_edge( int i, int j, graph_t * g) {
    if( i > 0 && i <= g->N && j > 0 && j <= g->N && i != j ) {
        g->adj_matrix[i][j] = 0;
        g->adj_matrix[j][i] = 0;
    }
}

void print_graph( graph_t * g) {
    int i,j;
    for(i = 0; i < g->N; i++)
     {
         for(j = 0; j < g->N; j++)
         {
             printf("%d ", g->adj_matrix[i][j]);
         }
         printf("\n");
     }
}

void free_graph( graph_t * g) {
    int i;
    for( i = 0; i < g->N; i++) {
        free( g -> adj_matrix[i]);
    }
    free(g -> adj_matrix);
    free(g);
}



int main() {
    int i, N, M, v1, v2;
    scanf("%d", &N);
    graph_t * g = create_graph(N);
    scanf("%d", &M);
    for( i = 0; i < M; i++) {
        scanf("%d %d", &v1, &v2);
        add_edge( v1, v2, g);
    }
    print_graph(g);

    free_graph(g);
    return 0;
    
}

