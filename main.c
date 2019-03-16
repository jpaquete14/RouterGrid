#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Graph {
    int N;  //number of nodes//
    int** adj_matrix; //adjacency matrix//
} * graph;

typedef struct master_node {
    int size, id;
    link head;
}* list;

typedef struct node {
    int value, size;
    struct node * next;
} * link;


graph create_graph( int N);
void add_edge( int i, int j, graph g);
void delete_edge( int i, int j, graph g);
void delete_node( int n, graph g);
void print_graph( graph g);
void free_graph( graph g);


int get_size(list l);
int get_id(list l);
list list_init();
void push(list l, int i);
void pop( list l);
link search_list(list l, int n);
void destroy_list(list l);


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
    if( i > 0 && i < g->N && j > 0 && j < g->N && i != j ) {
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

int get_size(list l) {
    return l->size;
}

int get_id(list l) {
    return l->id;
}

list list_init() {
    list l = (list)malloc(sizeof(struct master_node));
    l->head = NULL;
    l->size = 0;
    l->id = 0;
}

void push(list l, int i) {
    link new = malloc(sizeof(struct node));
    new->value = i;
    new->next = l->head;
    l->size++;
    if(i > l->id) l->id = i;
}

void pop(list l) {
    if (l->head == NULL) return;
    link old = l->head;
    l->head = old->next;
    free(old);
    l->size--;
}

link search_list(list l, int n) {
    for (link current = l->head; current != NULL; current = current->next) {
        if (current->value == n) return current;
    }
    return NULL;
}

void destroy_list(list l) {
    link current, aux;
    if (l == NULL) return;
    if (l->size != 0)
        for (current = l->head; aux = l->head->next; current != NULL) {
            aux = current->next;
            free(current); 
            current = aux;
        } 
    free(l);
}

/*================================================================
 * main functions
 * ===============================================================
 */

int main() {
    int i, N, M, v1, v2;
    int time = 0;
    master_list components = master_list_init(); //TODO
    master_list components_v2 = master_list_init(); //TODO
    list articulation = list_init();
    scanf("%d", &N);
    int visited[N], low[N], disc[N], parent[N];
    for(i = 0; i < N; i++) {
        visited[i] = 0;
        disc[i] = 0;
        parent[i] = -1;
    }
    graph g = create_graph(N);
    scanf("%d", &M);
    for(i = 0; i < N; i++) {
        scanf("%d %d", &v1, &v2);
        add_edge(v1, v2, g);
    }

    for(i = 0; i < N; i++) {
        if(visited[i] == 0) {
            list component = list_init();
            find_component(g, time, components, component, articulation, visited, low, disc, parent, i); //TODO
            add_list(components, component); //TODO
        }
    }

    for(i = 0; i < N; i++) {
        visited[i] = 0;
        disc[i] = 0;
        parent[i] = -1;
        if(search_list(articulation, i) != NULL){
            delete_node(g, i);
            visited[i] = -1;
        }
    }

    for(i = 0; i < N; i++) {
        if(visited[i] == 0) {
            list component = list_init();
            find_component(g, time, components_v2, component, NULL, visited, low, disc, parent, i); //TODO
            add_list(components_v2, component); //TODO
        }
    }

    printf("%d\n", components->size);
    print_components_id(components); //TODO
    printf("%d\n", articulation->size);
    print_biggest_component(components_v2); //TODO

    return 0;

}