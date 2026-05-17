#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#include "../include/query.h"
#include "../include/heap.h"

/* =========================================================
 * query.c
 * Parsarea și dispatcharea interogărilor de graf:
 *   EXISTS, EDGE, NEIGHBORS, PATH (BFS), DIJKSTRA
 * ========================================================= */

 /* Helper process path --- afiseaza drumul*/
static void print_path_recursive(const Graph *g, const int *parent, int id)
{
    if(parent[id] != -1) {
        print_path_recursive(g, parent, parent[id]);
        printf(" -> ");
    }

    printf("%s", g->nodes[id].entity.name);
}

/*Helper BFS --- face BFS cu vector pe post de coada*/
static int bfs_fill_parent(const Graph *g, int src_id, int *visited, int *parent)
{
    int *queue;
    int head = 0;
    int tail = 0;

    queue = malloc(g->size * sizeof(int));
    if(queue == NULL)
        return -1;

    visited[src_id] = 1;
    queue[tail++] = src_id;

    while(head < tail) {
        int current = queue[head++];
        EdgeNode *edge = g->nodes[current].edges;

        while(edge != NULL) {
            int next = edge->dest_id;

            if(!visited[next]) {
                visited[next] = 1;
                parent[next] = current;
                queue[tail++] = next;
            }

            edge = edge->next;
        }
    }

    free(queue);
    return 0;
}

/*Helper BFS --- afisare*/
static void print_bfs_result(const Graph *g, const int *visited, const int *parent, int dest_id)
{
    if(!visited[dest_id]) {
        printf("NU\n");
        return;
    }

    print_path_recursive(g, parent, dest_id);
    printf("\n");
}

/* ----------------------------------------------------------
 * Helper de parsare
 * ---------------------------------------------------------- */
static int is_separator(char c) {
    return c == '\0' || c == ' ' || c == '\t' || c == '\r' || c == '\n';
}

QueryType parse_query_type(const char *line)
{
    if(line == NULL)
        return Q_UNKNOWN;
    /* verific primul cuvant din linie; folosesc o functie auxiliara,
    pentru a testa caracterul de dupa cuvant. ex: EXISTS si EXISTSX */
    
        if(strncmp(line, "EXISTS", 6) == 0 && is_separator(line[6]))
        return Q_EXISTS;

    if(strncmp(line, "EDGE", 4) == 0 && is_separator(line[4]))
        return Q_EDGE;

    if(strncmp(line, "NEIGHBORS", 9) == 0 && is_separator(line[9]))
        return Q_NEIGHBORS;

    if(strncmp(line, "PATH", 4) == 0 && is_separator(line[4]))
        return Q_PATH;

    if(strncmp(line, "DIJKSTRA", 8) == 0 && is_separator(line[8]))
        return Q_DIJKSTRA;

    return Q_UNKNOWN;
}

/* ----------------------------------------------------------
 * EXISTS
 * ---------------------------------------------------------- */

void process_exists(const BST *tree, const char *name)
{
    /* TODO: caută în BST, afișează DA/NU */

    if(name == NULL)
        return;
    
    GraphNode *found = bst_search(tree, name);
    
    if(found != NULL)
        printf("EXISTS %s: DA\n", name);
    else
        printf("EXISTS %s: NU\n", name);
}

/* ----------------------------------------------------------
 * EDGE
 * ---------------------------------------------------------- */

void process_edge(const Graph *g, const BST *tree, const char *src_name, const char *dest_name)
{
    /* TODO: găsește ambele noduri via BST, scanează lista de muchii
     *       a sursei pentru destinație */
    
     GraphNode *src;
     GraphNode *dest;
     EdgeNode *edge;
     
     if(g == NULL || tree == NULL || src_name == NULL || dest_name == NULL)
        return;

    src = bst_search(tree, src_name);
    dest = bst_search(tree, dest_name);

    if(src == NULL || dest == NULL) {
        printf("EDGE %s %s: NU\n", src_name, dest_name);
        return;
    }

    edge = src->edges;

    while(edge != NULL) {
        if(edge->dest_id == dest->entity.id) {
            printf("EDGE %s %s: DA\n", src_name, dest_name);
            return;
        }

        edge = edge->next;
    }

    printf("EDGE %s %s: NU\n", src_name, dest_name);
}

/* ----------------------------------------------------------
 * NEIGHBORS
 * ---------------------------------------------------------- */

void process_neighbors(const Graph *g, const BST *tree, const char *name)
{
    /* TODO: găsește nodul, iterează lista de muchii, afișează
     *       numele vecinilor; dacă nu există muchii de ieșire
     *       afișează "NEIGHBORS <name>: NULL" */
    GraphNode *node;
    EdgeNode *edge;

    if(g == NULL || tree == NULL || name == NULL)
        return;
    node = bst_search(tree, name);
    
    printf("NEIGHBORS %s:", name);
    
    if(node == NULL || node->edges == NULL) {
        printf(" NULL\n");
        return;
    }

    edge = node->edges;

    while(edge != NULL) {
        GraphNode *dest = graph_get_node(g, edge->dest_id);

        if(dest != NULL)
            printf(" %s", dest->entity.name);

        edge = edge->next;
    }

    printf("\n");
}

/* ----------------------------------------------------------
 * PATH (BFS)
 * ---------------------------------------------------------- */

void process_path_bfs(const Graph *g, const BST *tree, const char *src_name, const char *dest_name)
{
    if(g == NULL || tree == NULL || src_name == NULL || dest_name == NULL)
        return;
    GraphNode *src;
    GraphNode *dest;
    int *visited, *parent;  //folosim un vector pe post de coada
    int src_id, dest_id;

    src = bst_search(tree , src_name);
    dest = bst_search(tree, dest_name);
    if(src == NULL || dest == NULL) {
        printf("PATH %s %s: NU\n", src_name, dest_name);
        return;
    }

    visited = calloc(g->size, sizeof(int));
    parent = malloc(g->size * sizeof(int));

    if(visited == NULL || parent == NULL) {
        free(visited);
        free(parent);
        return;
    }
     for(int i = 0; i < g->size; i++)
        parent[i] = -1;

    src_id = src->entity.id;
    dest_id = dest->entity.id;

    if(bfs_fill_parent(g, src_id, visited, parent) < 0) {
        free(visited);
        free(parent);
        return;
    }
    printf("PATH %s %s: ", src_name, dest_name);
    print_bfs_result(g, visited, parent, dest_id);

    free(visited), free(parent);
}



/*Helper DIJKSTRA --- initializarea nodurilor cu cost infinit*/

static void init_dijkstra(int n, float *dist, int *parent, int *visited)
{
    for(int i = 0; i < n; i++) {
        dist[i] = FLT_MAX;
        parent[i] = -1;
        visited[i] = 0;
    }
}

/*Helper DIJKSTRA --- completarea parintiilor pentru reconstruirea drumului */

static int dijkstra_fill_parent(const Graph *g, int src_id, int dest_id, float *dist, int *parent, int *visited)
{
    MinHeap *heap = heap_create(g->size);
    if(heap == NULL) return -1;

    dist[src_id] = 0.0f; //seteaza distanta nodului sursa la 0
    if(heap_push(heap, src_id, 0.0f) < 0) {
        heap_free(heap);
        return -1;
    }
    while(!heap_is_empty(heap)) {
        HeapNode current = heap_pop(heap);
        int u = current.node_id;
        EdgeNode *edge = g->nodes[u].edges;
        if(visited[u])  //daca nodul a fost deja procesat
            continue;
        visited[u] = 1;
        if(u == dest_id)    
            break;
        while(edge != NULL) {
            int v = edge->dest_id;
            float new_dist = dist[u] + edge->cost;
            if(!visited[v] && new_dist < dist[v]) {
                int status;
                dist[v] = new_dist;
                parent[v] = u;
                status = heap_decrease_key(heap, v, new_dist);
                if(status == 1)
                    status = heap_push(heap, v, new_dist);
                if(status < 0) {
                    heap_free(heap);
                    return -1;
                }
            }
            edge = edge->next;
        }
    }
    heap_free(heap);
    return 0;
}

/* ----------------------------------------------------------
 * DIJKSTRA
 * ---------------------------------------------------------- */

void process_dijkstra(const Graph *g, const BST *tree, const char *src_name, const char *dest_name)
{
    if(g == NULL || tree == NULL || src_name == NULL || dest_name == NULL) return;
    GraphNode *src = bst_search(tree, src_name);
    GraphNode *dest = bst_search(tree, dest_name);

    if(src == NULL || dest == NULL) {
        printf("DIJKSTRA %s %s: NU\n", src_name, dest_name);
        return;
    }

    float *dist = malloc(g->size * sizeof(float));
    int *parent = malloc(g->size * sizeof(int));
    int *visited = malloc(g->size * sizeof(int));

    if(dist == NULL || parent == NULL || visited == NULL) {
        free(dist);
        free(parent);
        free(visited);
        return;
    }

    init_dijkstra(g->size, dist, parent, visited);
    int src_id = src->entity.id;
    int dest_id = dest->entity.id;

    if(dijkstra_fill_parent(g, src_id, dest_id, dist, parent, visited) == 0) {
        printf("DIJKSTRA %s %s: ", src_name, dest_name);
        if(dist[dest_id] == FLT_MAX)
            printf("NU\n");
        else {
            printf("COST = %.2f; DRUM = ", dist[dest_id]);
            print_path_recursive(g, parent, dest_id);
            printf("\n");
        }
    }
    free(dist);
    free(parent);
    free(visited);
}

/* ----------------------------------------------------------
 * Dispatcher batch
 * ---------------------------------------------------------- */

void process_all_queries(Queue *q, const Graph *g, const BST *tree)
{
    char *line;

    if(q == NULL)
        return;

     while(!queue_is_empty(q)) {
        QueryType type;
        char *cmd;
        char *arg1;
        char *arg2;

        line = queue_dequeue(q);
        if(line == NULL)
            continue;

        type = parse_query_type(line);
        cmd = strtok(line, " \t\r\n");
        (void)cmd;

        arg1 = strtok(NULL, " \t\r\n");
        arg2 = strtok(NULL, " \t\r\n");

        if(type == Q_EXISTS && arg1 != NULL)
            process_exists(tree, arg1);
        else if(type == Q_EDGE && arg1 != NULL && arg2 != NULL)
            process_edge(g, tree, arg1, arg2);
        else if(type == Q_NEIGHBORS && arg1 != NULL)
            process_neighbors(g, tree, arg1);
        else if(type == Q_PATH && arg1 != NULL && arg2 != NULL)
            process_path_bfs(g, tree, arg1, arg2);
        else if(type == Q_DIJKSTRA && arg1 != NULL && arg2 != NULL)
            process_dijkstra(g, tree, arg1, arg2);

        free(line);
     }
}
