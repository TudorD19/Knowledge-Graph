#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "../include/heap.h"

/* =========================================================
 * heap.c
 * Min-heap de perechi (node_id, dist) pentru Dijkstra.
 * Folosește un tablou dinamic cu indexarea standard
 * părinte/copil:
 *   parinte(i)       = (i - 1) / 2
 *   copil_stang(i)   = 2 * i + 1
 *   copil_drept(i)   = 2 * i + 2
 * ========================================================= */

/* ----------------------------------------------------------
 * Helper intern de swap
 * ---------------------------------------------------------- */

static void swap(HeapNode *a, HeapNode *b) __attribute__((unused));
static void swap(HeapNode *a, HeapNode *b)
{
    /* TODO: interschimbă cele două elemente HeapNode */
    (void)a;
    (void)b;
}

/* ----------------------------------------------------------
 * Funcții de sift
 * ---------------------------------------------------------- */

static void sift_up(MinHeap *h, int i) __attribute__((unused));
static void sift_up(MinHeap *h, int i)
{
    /* TODO: mută elementul de la indexul i în sus până când
     *       proprietatea heap este respectată */
    (void)h;
    (void)i;
}

static void sift_down(MinHeap *h, int i) __attribute__((unused));
static void sift_down(MinHeap *h, int i)
{
    /* TODO: mută elementul de la indexul i în jos până când
     *       proprietatea heap este respectată */
    (void)h;
    (void)i;
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

MinHeap *heap_create(int initial_capacity)
{
    /* TODO: alocă MinHeap și tabloul său de date */
    (void)initial_capacity;
    return NULL;
}

void heap_free(MinHeap *h)
{
    /* TODO: eliberează tabloul de date, apoi structura */
    (void)h;
}

/* ----------------------------------------------------------
 * Operații de bază
 * ---------------------------------------------------------- */

int heap_push(MinHeap *h, int node_id, float dist)
{
    /* TODO: adaugă elementul, extinde dacă e necesar, execută sift up */
    (void)h;
    (void)node_id;
    (void)dist;
    return -1;
}

HeapNode heap_pop(MinHeap *h)
{
    /* TODO: interschimbă rădăcina cu ultimul element, micșorează,
     *       execută sift down, returnează vechea rădăcină */
    HeapNode rezultat = {-1, FLT_MAX};
    (void)h;
    return rezultat;
}

int heap_is_empty(const MinHeap *h)
{
    /* TODO: returnează 1 când size == 0 */
    (void)h;
    return 1;
}

int heap_decrease_key(MinHeap *h, int node_id, float new_dist)
{
    /* TODO: găsește node_id, actualizează dist dacă e mai mic,
     *       execută sift up */
    (void)h;
    (void)node_id;
    (void)new_dist;
    return -1;
}
