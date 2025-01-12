#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    double data;
    struct node *next;
} Node;

typedef struct queue {
    Node *head;
    Node *tail;
    size_t size;
} Queue;

void enqueue(Queue *q, double data) 
{
    Node *new_node = malloc(sizeof(Node));
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

int main(void) {
    Queue q = {NULL, NULL, 0};

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    enqueue(&q, 4);

    while(q.size > 0) {
        printf("%f\n", dequeue(&q));
    }
}