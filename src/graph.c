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
    /* TODO: returnează șir cu litere mici pentru fiecare enum de relație */
    (void)type;
    return "unknown";
}

RelationType str_to_relation_type(const char *str)
{
    /* TODO: parsează șirul relației la valoarea enum */
    (void)str;
    return (RelationType)-1;
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

Graph *graph_create(int initial_capacity)
{
    /* TODO: alocă structura Graph și tabloul de noduri */
    (void)initial_capacity;
    return NULL;
}

void graph_free(Graph *g)
{
    /* TODO: eliberează șirul de nume al fiecărui nod și lista de muchii,
     *       apoi tabloul și structura */
    (void)g;
}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int graph_add_node(Graph *g, const char *name, EntityType type)
{
    /* TODO: extinde tabloul dacă e necesar, inițializează noul GraphNode,
     *       returnează id-ul */
    (void)g;
    (void)name;
    (void)type;
    return -1;
}

int graph_add_edge(Graph *g, int src_id, int dest_id,
                   RelationType type, float cost)
{
    /* TODO: alocă EdgeNode, adaugă la finalul listei de muchii a sursei
     *       pentru a păstra ordinea de inserare */
    (void)g;
    (void)src_id;
    (void)dest_id;
    (void)type;
    (void)cost;
    return -1;
}

/* ----------------------------------------------------------
 * Funcții ajutătoare pentru interogare
 * ---------------------------------------------------------- */

int graph_find_id(const Graph *g, const char *name)
{
    /* TODO: scanare liniară returnând id-ul potrivit sau -1 */
    (void)g;
    (void)name;
    return -1;
}

GraphNode *graph_get_node(const Graph *g, int id)
{
    /* TODO: verifică limitele și returnează pointerul */
    (void)g;
    (void)id;
    return NULL;
}

/* ----------------------------------------------------------
 * Afișare
 * ---------------------------------------------------------- */

void graph_print(const Graph *g)
{
    /* TODO: afișează fiecare nod și lista sa de muchii */
    (void)g;
}
