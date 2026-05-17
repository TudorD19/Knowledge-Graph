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
    HeapNode tmp;

    tmp = *a;
    *a = *b;
    *b = tmp;
}

/* ----------------------------------------------------------
 * Funcții de sift
 * ---------------------------------------------------------- */

static void sift_up(MinHeap *h, int i) __attribute__((unused));
static void sift_up(MinHeap *h, int i)
{
    /* TODO: mută elementul de la indexul i în sus până când
     *       proprietatea heap este respectată */
    while(i > 0) {
        int parent = (i - 1) / 2;

        if(h->data[parent].dist <= h->data[i].dist) //daca parintele are dist <= decat copilul
            break;
        
        swap(&h->data[parent], &h->data[i]);
        i = parent;
    }
}

static void sift_down(MinHeap *h, int i) __attribute__((unused));
static void sift_down(MinHeap *h, int i)
{
    /* TODO: mută elementul de la indexul i în jos până când
     *       proprietatea heap este respectată */
    while(1) { 
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if(left < h->size && h->data[left].dist < h->data[smallest].dist)
            smallest = left;

        if(right < h->size && h->data[right].dist < h->data[smallest].dist)
            smallest = right;
        
        if(smallest == i)
            break;
        
        swap(&h->data[i], &h->data[smallest]);
        i = smallest;
    }
}

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

MinHeap *heap_create(int initial_capacity)
{
    if(initial_capacity <= 0)
        return NULL;

    MinHeap *h = malloc(sizeof(MinHeap));

    if(h == NULL)
        return NULL;
    
    h->data = malloc(initial_capacity * sizeof(HeapNode));

    if(h->data == NULL) {
        free(h);
        return NULL;
    }

    h->size = 0;
    h->capacity = initial_capacity;

    return h;
}

void heap_free(MinHeap *h)
{
    if(h == NULL)
        return;
    free(h->data);
    free(h);
}

/* ----------------------------------------------------------
 * Operații de bază
 * ---------------------------------------------------------- */

int heap_push(MinHeap *h, int node_id, float dist)
{
    /* TODO: adaugă elementul, extinde dacă e necesar, execută sift up */
    HeapNode *tmp;
    int index;

    if(h == NULL)
        return -1;

    //dublare capacitate
    if(h->size == h->capacity) {
        int new_capacity = h->capacity * 2;
        tmp = realloc (h->data, new_capacity * sizeof(HeapNode));

        if(tmp == NULL)
            return -1;

        h->data = tmp;
        h->capacity = new_capacity;
    }

    index = h->size;

    h->data[index].node_id = node_id;
    h->data[index].dist = dist;

    h->size ++;
    sift_up(h, index);

    return 0;
}

HeapNode heap_pop(MinHeap *h)
{
    /* TODO: interschimbă rădăcina cu ultimul element, micșorează,
     *       execută sift down, returnează vechea rădăcină */
    HeapNode rezultat = {-1, FLT_MAX};
    
    if(h == NULL || h->size == 0)
        return rezultat;

    rezultat = h->data[0];

    h->data[0] = h->data[h->size - 1];
    h->size--;

    if(h->size > 0)
        sift_down(h, 0);

    return rezultat;
}

int heap_is_empty(const MinHeap *h)
{
    if(h == NULL || h->size == 0)
        return 1;
    
    return 0;
}

int heap_decrease_key(MinHeap *h, int node_id, float new_dist)
{
    if(h == NULL)
        return -1;
    
    for(int i = 0 ; i < h->size ; i++) {
        if(h->data[i].node_id == node_id) {
            if(new_dist < h->data[i].dist) {
                h->data[i].dist = new_dist;
                sift_up(h, i);  //distanta devine mai mica --- sift_up
            }
            return 0;
        }
    }
    return 1;
}
