#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/queue.h"

/* =========================================================
 * queue.c
 * Coadă FIFO susținută de o listă simplu înlănțuită.
 * Stochează copii alocate pe heap ale șirurilor.
 * ========================================================= */

/* ----------------------------------------------------------
 * Ciclul de viață
 * ---------------------------------------------------------- */

Queue *queue_create(void)
{
    /* TODO: alocă și inițializează cu zero o structură Queue */
    return NULL;
}

void queue_free(Queue *q)
{
    /* TODO: golește coada eliberând fiecare nod și datele sale */
    (void)q;
}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int queue_enqueue(Queue *q, const char *data)
{
    /* TODO: duplică data, alocă QueueNode, adaugă la capătul rear */
    (void)q;
    (void)data;
    return -1;
}

char *queue_dequeue(Queue *q)
{
    /* TODO: elimină nodul din față, returnează datele sale (apelantul
     *       eliberează) */
    (void)q;
    return NULL;
}

/* ----------------------------------------------------------
 * Inspecție
 * ---------------------------------------------------------- */

int queue_is_empty(const Queue *q)
{
    /* TODO: returnează 1 când size == 0 */
    (void)q;
    return 1;
}

void queue_print(const Queue *q)
{
    /* TODO: iterează de la front la rear, afișează fiecare șir de date */
    (void)q;
}
