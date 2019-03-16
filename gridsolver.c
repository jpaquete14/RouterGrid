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

typedef struct list_node {
    node_t * list;
    struct list_node * next;
} list_node_t;

graph_t * create_graph( int N);
void add_edge( int i, int j, graph_t * g);
void delete_edge( int i, int j, graph_t * g);
void print_graph( graph_t * g);
void free_graph( graph_t * g);

node_t * create_list();
void add(int n, node_t * top);
int remove( node_t * top);

void add_list( list_node_t * l, node_t * n);

/*=======================================================
 *list functions
 *=======================================================
 */
node_t * create_list() {
    node_t * s = NULL;
    return s;
}

void add(int n, node_t * top) {
    node_t * new;
    new = (node_t *) malloc(sizeof(struct node));
    new->value = n;
    new->next = top;
    top = new; 
}


int remove( node_t * top) {
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

void free_list( node_t * top) {
    node_t * i;
    for(i = top; i != NULL; i = i->next) {
        free(i);
    }
}

/*=======================================================
 *list_node functions
 *=======================================================
 */

void add_list(list_node_t * l, node_t * n) {
    list_node_t * aux;
    aux->list = n;
    aux->next = l;
    l = aux;
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


/* =============================================================================
 * Graph algorithm
 * =============================================================================
 */

void rec_tarjan( graph_t * g, int time, int visited[], int u, int d[], int low[], int parent[], node_t * art_pts, list_node_t * comp_list) {
    int children = 0;
    int i;
    d[u] = low[u] = ++time;
    visited[u] = 1;
    for(i = 0; i < g->N; i++) {
        if(g->adj_matrix[u][i] == 1) {
            //If the node hasn't been accessed yet
            if( visited[i] == 0) {
                children++;
                parent[i] = u;
                
                rec_tarjan(g, time, visited, i, d, low, parent, art_pts);

                low[u] = min(low[u], low[i]);
                //when root with more than 1 child
                if(parent[u] == NULL && children > 1) {
                    add(u, art_pts);
                }
                //when not root but low value of child is >= than its discover value
                if(parent[u] != NULL && low[i] >= d[u]) {
                    add(u, art_pts);
                }
            }
            //If it isn't the parent node, update low value
            if( parent[u] != i) {
                low[u]  = min(low[u], d[i]);
            }
        }
    }
}


int main() {
    int i, N, M, v1, v2, time = 0;
    list_node_t * comp_list     //Saves the graph's separate components
    scanf("%d", &N);
    graph_t * g = create_graph(N);
    int visited[N], d[N], low[N], parent[N];
    for ( i = 0; i < N; i++) { 
        parent[i] = -1; 
        visited[i] = 0; 
    } 
    node_t * art_pts = create_list();   //Saves the articulation points
    
    scanf("%d", &M);
    for( i = 0; i < M; i++) {
        scanf("%d %d", &v1, &v2);
        add_edge( v1, v2, g);
    }
    print_graph(g);

    rec_tarjan( g, time, visited, 0, d, low, parent, art_pts, comp_list, );

    for(i = 0; i < N; i++) {
        if(visited[i] == 1) {
            add(i,)
        }
    }

    free_graph(g);
    return 0;
    
}

