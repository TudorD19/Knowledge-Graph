#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/graph.h"

/* =========================================================
 * graph.c
 * Implementarea grafului direcționat ponderat cu liste de
 * adiacență.
 * ========================================================= */

/* ----------------------------------------------------------
 * Funcții ajutătoare pentru relații
 * ---------------------------------------------------------- */

const char *relation_type_to_str(RelationType type)
{
    switch (type) {
        case WORKS_AT:
            return "works_at";
        case FRIEND_OF:
            return "friend_of";
        case LOCATED_IN:
            return "located_in";
        case PARTICIPATES_IN:
            return "participates_in";
        default:
            return "unknown";
    }
}

RelationType str_to_relation_type(const char *str)
{
    if(str == NULL) {
        return (RelationType)-1;
    }
    if (strcmp(str, "works_at") == 0) {
        return WORKS_AT;
    }

    if (strcmp(str, "friend_of") == 0) {
        return FRIEND_OF;
    }

    if (strcmp(str, "located_in") == 0) {
        return LOCATED_IN;
    }

    if (strcmp(str, "participates_in") == 0) {
        return PARTICIPATES_IN;
    }

    return (RelationType)-1;

}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

Graph *graph_create(int initial_capacity)
{
 Graph *g;

    //verificam daca are sens sa cream graful.

    if (initial_capacity <= 0)
        return NULL;

    g = malloc(sizeof(Graph));
    if(g == NULL) {
        return NULL;
    }

    g->nodes = calloc(initial_capacity, sizeof(*g->nodes));
    if(g->nodes == NULL) {
        free(g);
        return NULL;
    }

    g->size = 0;
    g->capacity = initial_capacity;

    return g;

}

void graph_free(Graph *g)
{
  //daca graful e null, nu avem ce elibera
    if(g == NULL)
        return;
    
    //pentru fiecare nod eliberam lista de muchii
    for(int i = 0 ; i < g->size ; i++) {
        EdgeNode *edge = g->nodes[i].edges;

        while(edge != NULL) {
            EdgeNode *tmp = edge;
            edge = edge->next;
            free(tmp);
        }

        //eliberam si numele alocat dinamic
        free(g->nodes[i].entity.name);
    }

    free(g->nodes);
    free(g);

}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int graph_add_node(Graph *g, const char *name, EntityType type)
{
  if(g == NULL || name == NULL)
        return -1;
    
    int id;
    char *name_copy;

    //daca vectorul de noduri este plin
    if(g->size == g->capacity) {
        int new_capacity = g->capacity * 2;
        GraphNode *tmp = realloc(g->nodes, (int)new_capacity * sizeof(GraphNode));

        if(tmp == NULL)
            return -1;

        g->nodes = tmp;
        g->capacity = new_capacity;

    }
    name_copy = malloc(strlen(name) + 1);
    
    if(name_copy == NULL) 
        return -1;

    strcpy(name_copy , name);

    id = g->size;

    g->nodes[id].entity.name = name_copy;
    g->nodes[id].entity.type = type;
    g->nodes[id].entity.id = id;
    g->nodes[id].edges = NULL;

    g->size++;

    return id;

}

int graph_add_edge(Graph *g, int src_id, int dest_id, RelationType type, float cost)
{
    EdgeNode *edge, *curr;
    // daca graful e NULL, return -1
    if(g == NULL)
        return -1;
    
    // daca nodul sursa are id-ul negativ sau depaseste numarul de noduri, return -1
    if(src_id < 0 || src_id >= g->size)
        return -1;

    // daca nodul destinatie are id-ul negativ sau depaseste numarul de noduri, return -1
    if(dest_id < 0 || dest_id >= g->size)
        return -1;

    // daca type este invalid, return -1
    if(type < WORKS_AT || type > PARTICIPATES_IN) 
        return -1;

    edge = malloc(sizeof(*edge));
        if(edge == NULL)
        return -1;

    edge->dest_id = dest_id;
    edge->type = type;
    edge->cost = cost;
    edge->next = NULL;

    // daca nodul sursa nu are un edge
    if(g->nodes[src_id].edges == NULL) {
        g->nodes[src_id].edges = edge;
        return 0;
    }
    curr = g->nodes[src_id].edges;     // daca exista deja muchii
    while(curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = edge; // parcurgem pana la ultima muchie, pentru a insera nould edge
    return 0;
}

/* ----------------------------------------------------------
 * Funcții ajutătoare pentru interogare
 * ---------------------------------------------------------- */

int graph_find_id(const Graph *g, const char *name)
{   
    if(g == NULL || name == NULL)
        return -1;

    // parcurgere de la 0 la nr noduri - 1    
    for(int i = 0 ; i < g->size ; i++) {
        if(strcmp(g->nodes[i].entity.name , name) == 0)
            return g->nodes[i].entity.id;
    }

    return -1;
}

GraphNode *graph_get_node(const Graph *g, int id)
{
    if(g == NULL)
        return NULL;
    if(id < 0 || id >= g->size)
        return NULL;

    return &g->nodes[id];
    
}

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

void graph_print(const Graph *g)
{
    if(g == NULL) 
        return;

    for(int i = 0 ; i < g->size ; i++) {
        EdgeNode *edge = g->nodes[i].edges;

        printf("%d %s:", g->nodes[i].entity.id, g->nodes[i].entity.name);

        while(edge != NULL) {

            // folosim functia relatio_type_to_str pentru a afisa stringul
            printf(" [%d %s %.2f]", edge->dest_id, relation_type_to_str(edge->type), edge->cost);

            edge = edge->next;
        }

        printf("\n");
    }
}
