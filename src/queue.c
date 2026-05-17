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
    Queue *q = malloc(sizeof(Queue));

    if(q == NULL)
        return NULL;
    
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;

    return q;
}

void queue_free(Queue *q)
{
    if(q == NULL)
        return;
    
    // folosim un nod curr pentru a ne plimba prin coada si elibera
    QueueNode *curr;    

    curr = q->front;

    while(curr != NULL) {
        //eliberam cu ajutorul unui nod temp
        QueueNode *tmp = curr;
        curr = curr->next;

        //fiecare nod va avea si o copie alocata dinamic a stringului
        free(tmp->data);
        free(tmp);
    }

    free(q);
}

/* ----------------------------------------------------------
 * Mutație
 * ---------------------------------------------------------- */

int queue_enqueue(Queue *q, const char *data)
{
        
    if(q == NULL || data == NULL)
        return -1;
    
    // node este un nod din coada
    QueueNode *node = malloc(sizeof(QueueNode));
    
    if(node == NULL)
        return -1;

    node->data = malloc(strlen(data) + 1);
    
    if(node->data == NULL) {
        free(node);
        return -1;
    }
    
    strcpy(node->data, data);
    node->data[strcspn(node->data, "\r\n")] = '\0';
    node->next = NULL;
    
    //daca este coada goala
    if(q->rear == NULL) {
        q->front = node;
        q->rear = node;
    }
    else {
        q->rear->next = node;
        q->rear = node;
    }

    q->size ++;

    return 0;
}

char *queue_dequeue(Queue *q)
{
    QueueNode *node;
    char *data;

    if(q == NULL || q->front == NULL)
        return NULL;
    
    node = q->front;
    data = node->data;
    q->front = q->front->next;

    if(q->front == NULL)
        q->rear = NULL;

    q->size--;

    free(node);

    return data;
}

/* ----------------------------------------------------------
 * Inspecție
 * ---------------------------------------------------------- */

int queue_is_empty(const Queue *q)
{
    if(q == NULL || q->size == 0)
        return 1;
    else 
        return 0;
}

void queue_print(const Queue *q)
{   
    QueueNode *curr;

    if(q == NULL)
        return;
    
    curr = q->front;

    while(curr != NULL) {
        printf("%s\n", curr->data);
        curr = curr->next;
    }
}
