#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct Graph {
    int N;  //number of nodes//
    int** adj_matrix; //adjacency matrix//
} * graph;

typedef struct node {
    int value;
    struct node * next;
} * link;

typedef struct master_node {
    int size, id;
    link head;
}* list;

typedef struct list_node {
    list head;
    struct list_node * next;
} * master_list;

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
void swap(link l1, link l2);
void bubbleSort(link start);
void print_list(list l);


master_list master_list_init();
master_list add_list(master_list m, list l);
void destroy_master_list(master_list m);
void print_master_list(master_list m);
void print_master_list_size(master_list components);
void print_components_id(master_list components);
void print_biggest_component( master_list components);



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
    return l;
}

void push(list l, int i) {
    link new = malloc(sizeof(struct node));
    new->value = i;
    new->next = l->head;
    l->head = new;
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
        for (current = l->head, aux = l->head->next; current != NULL; aux = current->next, free(current), current = aux){}
    free(l);
}

void swap(link l1, link l2) { 
    int aux = l1->value; 
    l1->value = l2->value; 
    l2->value = aux; 
}

void bubbleSort(link start) { 
    int swapped; 
    link l1; 
    link l2 = NULL; 
  
    //If list is empty
    if (start == NULL) return; 
    do { 
        swapped = 0;
        l1 = start;
        while (l1->next != l2) 
        { 
            if (l1->value > l1->next->value) 
            {  
                swap(l1, l1->next);
                swapped = 1;
            } 
            l1 = l1->next;
        }
        l2 = l1; 
    }
    while (swapped); 
} 

void print_list(list l) {
    link aux;
    printf("id: %d, size: %d\n", l->id, l->size);
    printf("(");
    for(aux = l->head; aux != NULL; aux = aux->next) {
        printf("%d ", aux->value);
    }
    printf(")\n");
}

/*================================================================
 * master_list functions
 * ===============================================================
 */

master_list master_list_init() {
    master_list new = (master_list)malloc(sizeof(struct list_node));
    new->head = NULL;
    new->next = NULL;
    return new;
}

master_list add_list(master_list m, list l) {
    master_list new = (master_list)malloc(sizeof(struct list_node));
    new->head = l;
    new->next = m;
    return new;
}

void destroy_master_list(master_list m) {
    master_list aux, current;
    for (current = m, aux = m->next; current != NULL; aux = current->next, destroy_list(current->head), current = aux){}
    free(m);
}

void print_master_list(master_list m) {
    master_list aux = m;
    list l;
    printf("(");
    for(l = aux->head; l != NULL; aux = aux->next, l = aux->head) {
        print_list(aux->head);
    }
    printf(")\n");
}

void print_master_list_size(master_list components) {
    int count = 0;
    master_list aux;
    for( aux = components; aux != NULL; aux = aux->next) {
        if(aux->head != NULL) count++;
    }
    printf("%d\n", count);
}

void print_components_id(master_list components) {
    link aux2;
    list ids = list_init();
    master_list aux;
    for( aux = components; aux != NULL; aux = aux->next) {
        if(aux->head != NULL) push( ids, aux->head->id);
    }
    bubbleSort(ids->head);
    for( aux2 = ids->head; aux2 != NULL; aux2 = aux2->next) {
        printf("%d ", (aux2->value+1));
    }
    printf("\n");
}

void print_biggest_component( master_list components) {
    int biggest = 0;
    master_list aux;
    for( aux = components; aux != NULL; aux = aux->next) {
        if(aux->head != NULL) {
            if( aux->head->size > biggest) biggest = aux->head->size;
        }
    }
    printf( "%d\n", biggest);
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
    push(component, u); //Saving the visited node in the component
    for(i = 0; i < g->N; i++) { printf("%d: %d\n", u, visited[i]); }
    for(i = 0; i < g->N; i++) {
        if(g->adj_matrix[u][i] == 1) {
            //If the node hasn't been accessed yet
            if( visited[i] == 0) {
                children++;
                parent[i] = u;
                
                find_component(g, time, component, articulation, visited, low, disc, parent, i);

                low[u] = min(low[u], low[i]);
                //when root with more than 1 child
                if(parent[u] == -1 && children > 1) {
                    if(search_list(articulation, u) == NULL) push(articulation, u);
                }
                //when not root but low value of child is >= than its discover value
                if(parent[u] != -1 && low[i] >= disc[u]) {
                    if(search_list(articulation, u) == NULL) push(articulation, u);
                }
            }
            //If it isn't the parent node, update low value
            if( parent[u] != i && visited[i] != -1) {
                low[u]  = min(low[u], disc[i]);
            }
        }
    }
}




int main() {
    int i, N, M, v1, v2;
    int time = 0;
    master_list components = master_list_init();   //List that saves the lists of components from the graph
    master_list components_v2 = master_list_init(); //List thats saves the components of the graph without the articulation points
    list articulation = list_init();    //List that saves the articulation points
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
    //Find the separate commponents of the graph
    //Find the articulation poitns of the graph
    for(i = 0; i < N; i++) {
        if(visited[i] == 0) {
            list component = list_init();
            find_component(g, time, component, articulation, visited, low, disc, parent, i);
            print_list(articulation);
            components = add_list(components, component);
            print_master_list(components);
        }
    }

    //Remove the articulation points of the graph
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
    //Find the components of the new graph
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