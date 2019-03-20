/* Joao Paquete n89477 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct node {
    int id;
    struct node * next;
} * link;

typedef struct Graph {   
    int N;    
    link *adj; 
} * graph;


link list_insert_begin(link l, int id);
void list_insert_end(link head, int id);
link list_remove(link l, int id);
void list_destroy(link l);
bool is_in_list(link l, int id);
void list_print(link l);

graph create_graph( int N);
void add_edge( int i, int j, graph g);
void delete_edge( int i, int j, graph g);
void delete_node( int n, graph g);
void print_graph( graph g);
void free_graph( graph g);


/*================================================================
 * list functions
 * ===============================================================
 */

link list_insert_begin(link l, int id) {
    link newNode = (link)malloc(sizeof(struct node));
    newNode->id = id;
    newNode->next = l;
    return newNode;
}


link list_remove(link l, int id) {
    link current, prev;
    if(l->id == id) {
        current = l->next;
        free(l);
        return current;
    }
    for(current = l; current != NULL; prev = current, current = current->next) {
        if(current->id == id) {
            prev->next = current->next;
            free(current);
            return l;
        }
    }
    return l;  
}
void list_destroy(link l) {
    link aux;
    while(l != NULL) {
        aux = l;
        l = l->next;
        free(aux);
    }
}

bool is_in_list(link l, int id) {
    link aux;
    for(aux = l; aux != NULL; aux = aux->next) {
        if(aux->id == id) return true;
    }
    return false;
}

void list_print(link l) {
    link current;
    for(current = l; current != NULL; current = current->next) {
        if(current->next == NULL) printf("%d\n", current->id+1);
        else printf("%d ", current->id+1);
    }
}

/*================================================================
 * Graph functions
 * ===============================================================
 */

graph create_graph( int N ) {
    int v;   
    graph G = (graph)malloc(sizeof(struct Graph));
    G->N = N;  
    G->adj = malloc(N * sizeof(link));   
    for (v = 0; v < N; v++) {  
        G->adj[v] = NULL;
    }   
    return G;
}

void add_edge( int i, int j, graph g) { 
    g->adj[i-1] = list_insert_begin(g->adj[i-1], j-1);   
    g->adj[j-1] = list_insert_begin(g->adj[j-1], i-1);   
}

void delete_edge( int i, int j, graph g) {
    g->adj[i] = list_remove(g->adj[i], j);   
    g->adj[j] = list_remove(g->adj[j], i);
}

void delete_node( int n, graph g) {
    int i;
    for(i = 0; i < g->N; i++) {
        if(is_in_list(g->adj[n], i)) {
            delete_edge(i, n, g);
        }
    }
}

void free_graph( graph g) {
    int i;
    for( i = 0; i < g->N; i++) {
        list_destroy( g -> adj[i]);
    }
    free(g->adj);
    free(g);
}

void print_graph( graph g) {
    int i;
    printf("\n");
    for(i = 0; i < g->N; i++) {
        list_print(g->adj[i]);
    }
    printf("\n");
}

/*================================================================
 * main functions
 * ===============================================================
 */

int min( int a, int b){ 
    if(a >= b) return b;
    else return a;
}
/*Receives the graph and some other tools to determine one component of the graph*/
/*It also flags any articulation points it finds*/
void find_component( graph g, int * time, int articulation[], int visited[], int low[], int disc[], int parent[], int * size, int u) {
    int children = 0;
    link current;
    (*size)++;  /*number of nodes in the component*/
    disc[u] = low[u] = ++(* time);
    visited[u] = 1;
    for(current = g->adj[u]; current != NULL; current = current->next) {

        /*If the node has been flagged as a articulation point, ignore it*/
        if( visited[current->id] == -1) continue;

        /*If the node hasn't been accessed yet*/
        if( visited[current->id] == 0) {
            children++;
            parent[current->id] = u;
            find_component(g, time, articulation, visited, low, disc, parent, size, current->id);
            low[u] = min(low[u], low[current->id]);
            /*when root with more than 1 child*/
            if(parent[u] == -1 && children > 1) {
                articulation[u] = 1;
            }
            /*when not root but low value of child is >= than its discover value*/
            if(parent[u] != -1 && low[current->id] >= disc[u]) {
                articulation[u] = 1;
            }
        }
        /*If it isn't the parent node, update low value*/
        if( parent[u] != current->id && visited[current->id] != -1) {
            low[u]  = min(low[u], disc[current->id]);
        }
    }
}




int main() {
    int i, N, M, v1, v2;
    int timee = 0, size = 0, count = 0, biggest = 0;
    int * size_p = &size;
    int * time_p = &timee;
    link components = NULL;
    scanf("%d", &N);
    int * visited = (int*)malloc(N * sizeof(int));
    memset(visited, 0, N * sizeof(visited[0]));
    int * low = (int*)malloc(N * sizeof(int));
    memset(low, -1, N * sizeof(low[0]));
    int * disc = (int*)malloc(N * sizeof(int));
    memset(disc, 0, N * sizeof(disc[0]));
    int * parent = (int*)malloc(N * sizeof(int));
    memset(parent, -1, N * sizeof(parent[0]));
    int * articulation = (int*)malloc(N * sizeof(int));
    memset(articulation, 0, N * sizeof(articulation[0]));
    graph g = create_graph(N);
    scanf("%d", &M);
    for(i = 0; i < M; i++) {
        scanf("%d %d", &v1, &v2);
        add_edge(v1, v2, g);
    }
    
    /*/Find the separate commponents of the graph/*/
    /*/Find the articulation points of the graph/*/
    for(i = (N-1); i >= 0; i--) {
        if(visited[i] == 0) {
            find_component(g, time_p, articulation, visited, low, disc, parent, size_p, i);
            components = list_insert_begin(components, i);
            count++;
        }
    }

    /*Print the first 3 outputs*/
    printf("%d\n", count); 
    list_print(components);
    list_destroy(components);
    count = 0;
    for(i = 0; i < N; i++) {
        if(articulation[i] == 1){
            count++;
        }
    }
    printf("%d\n", count); 


    *time_p = 0; *size_p = 0;
    for(i = 0; i < N; i++) {
        visited[i] = 0;
        disc[i] = 0;
        parent[i] = -1;
        /*flags the articulation points, so they don't get accessed in the next stage*/
        if(articulation[i] == 1){
            visited[i] = -1;
        }
    }
    /*Find the components of the graph without the articulation points*/
    for(i = 0; i < N; i++) {
        if(visited[i] == 0) {
            find_component(g, time_p, articulation, visited, low, disc, parent, size_p, i);
            /*flag that saves the biggest component found in the graph*/
            if(*size_p > biggest) biggest = *size_p;
            *size_p = 0;
        }
    }
    
    /*4th output*/
    printf("%d\n", biggest);

    free_graph(g);
    free(visited);
    free(low);
    free(disc);
    free(parent);
    free(articulation);

    return 0;

}