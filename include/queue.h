#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>
#include <stdlib.h>
#define NAN (__builtin_nanf (""))

// Node structure for the queue
typedef struct node {
    double data;
    struct node *next;
} Node;

// Queue structure
typedef struct queue {
    Node *head;
    Node *tail;
    size_t size;
} Queue;

// Function to add an element to the queue
void enqueue(Queue *q, double data) 
{
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;

    if(q->size == 0) {
        q->head = new_node;
        q->tail = new_node;
    } else {
        q->tail->next = new_node;
        q->tail = new_node;
    }

    q->size = q->size + 1;
}

double dequeue(Queue *q) {
    if(q->size == 0) return NAN;
    double data = q->head->data;
    Node *tmp = q->head;
    q->head = q->head->next;
    q->size = q->size - 1;
    free(tmp);
    return data;
}

void queue_destroy(Queue *q) {
    while(q->size > 0) dequeue(q);
}

#endif // QUEUE_H
