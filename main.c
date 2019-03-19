#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct Graph {
    int N;  /*/number of nodes/*/
    int** adj_matrix; /*/adjacency matrix/*/
} * graph;

typedef struct node {
    int id;
    int size;
    struct node * next;
} * link;


graph create_graph( int N);
void add_edge( int i, int j, graph g);
void delete_edge( int i, int j, graph g);
void delete_node( int n, graph g);
void print_graph( graph g);
void free_graph( graph g);

link list_insert(link l, int id, int size);
link list_remove(link l, int id);
void list_destroy(link l);
bool is_in_list(link l, int id);



/*================================================================
 * Graph functions
 * ===============================================================
 */

graph create_graph( int N ) {
    int i, j;
    graph g = (graph)malloc(sizeof(struct Graph));
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

void add_edge( int i, int j, graph g) {
    if( i > 0 && i <= g->N && j > 0 && j <= g->N && i != j ) {
        i = i-1;
        j = j-1;
        g->adj_matrix[i][j] = 1;
        g->adj_matrix[j][i] = 1;
    }
}

void delete_edge( int i, int j, graph g) {
    if( i > 0 && i < g->N && j > 0 && j < g->N && i != j ) {
        g->adj_matrix[i][j] = 0;
        g->adj_matrix[j][i] = 0;
    }
}

void delete_node( int n, graph g) {
    int i;
    for(i = 0; i < g->N; i++) {
        delete_edge(i, n, g);
    }
}

void free_graph( graph g) {
    int i;
    for( i = 0; i < g->N; i++) {
        free( g -> adj_matrix[i]);
    }
    free(g -> adj_matrix);
    free(g);
}

void print_graph( graph g) {
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


/*================================================================
 * list functions
 * ===============================================================
 */

link list_insert(link l, int id, int size) {
    link new = (link)malloc(sizeof(struct node));
    new->id = id;
    new->size = size;
    new->next = l;
    return new;
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


/*================================================================
 * main functions
 * ===============================================================
 */

int min( int a, int b){ 
    if(a >= b) return b;
    else return a;
}

void find_component( graph g, int time, list component, list articulation, int visited[], int low[], int disc[], int parent[], int u) {
    int children = 0;
    int i;
    disc[u] = low[u] = ++time;
    visited[u] = 1;
    push(component, u); /*/Saving the visited node in the component/*/
    for(i = 0; i < g->N; i++) { printf("%d: %d\n", u, visited[i]); }
    for(i = 0; i < g->N; i++) {
        if(g->adj_matrix[u][i] == 1) {
            /*/If the node hasn't been accessed yet/*/
            if( visited[i] == 0) {
                children++;
                parent[i] = u;
                
                find_component(g, time, component, articulation, visited, low, disc, parent, i);

                low[u] = min(low[u], low[i]);
                /*/when root with more than 1 child/*/
                if(parent[u] == -1 && children > 1) {
                    if(search_list(articulation, u) == NULL) push(articulation, u);
                }
                /*/when not root but low value of child is >= than its discover value/*/
                if(parent[u] != -1 && low[i] >= disc[u]) {
                    if(search_list(articulation, u) == NULL) push(articulation, u);
                }
            }
            /*/If it isn't the parent node, update low value/*/
            if( parent[u] != i && visited[i] != -1) {
                low[u]  = min(low[u], disc[i]);
            }
        }
    }
}




int main() {
    int i, N, M, v1, v2;
    int time = 0;
    master_list components = master_list_init();   /*/List that saves the lists of components from the graph/*/
    master_list components_v2 = master_list_init(); /*/List thats saves the components of the graph without the articulation points/*/
    list articulation = list_init();    /*/List that saves the articulation points/*/
    scanf("%d", &N);
    int visited[N], low[N], disc[N], parent[N];
    for(i = 0; i < N; i++) {
        visited[i] = 0;
        disc[i] = 0;
        parent[i] = -1;
    }
    graph g = create_graph(N);
    scanf("%d", &M);
    for(i = 0; i < M; i++) {
        scanf("%d %d", &v1, &v2);
        printf("Saved the %d\n", i);
        add_edge(v1, v2, g);
    }

    print_graph(g);
    /*/Find the separate commponents of the graph/*/
    /*/Find the articulation poitns of the graph/*/
    for(i = 0; i < N; i++) {
        if(visited[i] == 0) {
            list component = list_init();
            find_component(g, time, component, articulation, visited, low, disc, parent, i);
            print_list(articulation);
            components = add_list(components, component);
            print_master_list(components);
        }
    }

    /*/Remove the articulation points of the graph/*/
    time = 0;
    for(i = 0; i < N; i++) {
        visited[i] = 0;
        disc[i] = 0;
        parent[i] = -1;
        if(search_list(articulation, i) != NULL){
            delete_node(i, g);
            visited[i] = -1;
        }
    }
    /*/Find the components of the new graph/*/
    for(i = 0; i < N; i++) {
        if(visited[i] == 0) {
            list component = list_init();
            find_component(g, time, component, NULL, visited, low, disc, parent, i);
            print_list(component);
            components_v2 = add_list(components_v2, component);
            print_master_list(components_v2);
        }
    }

    print_master_list_size(components); 
    print_components_id(components); 
    printf("%d\n", articulation->size);
    print_biggest_component(components_v2);

    return 0;

}