#include <stdio.h>
#include <stdlib.h>
#define NAN (__builtin_nanf (""))

typedef struct queue {
    double *queue;
    int head;
    int tail;
    size_t size;
    size_t capacity;
} Queue;

Queue queue_create(size_t capacity) {
    return (Queue) {malloc(capacity * sizeof(Queue)), -1, -1, 0,capacity};
}

void enqueue(Queue *q, double data) {
    if(q->capacity == q->size) return;
    if(q->head == -1) q->head = 0;
    q->tail = (q->tail + 1) % q->capacity;
    q->queue[q->tail] = data;
    q->size++;
}

double dequeue(Queue *q) {
    if(q->size == 0) return NAN;
    double data = q->queue[q->head];
    if(q->size == 1) {
        q->head = -1;
        q->tail = -1;
    } else q->head = (q->head + 1) % q->capacity;
    q->size--;
    return data;
}

int main(void) {
    Queue q = queue_create(3);

    enqueue(&q, 1);
    enqueue(&q, 2);
    enqueue(&q, 3);
    enqueue(&q, 4);
    enqueue(&q, 5);
    enqueue(&q, 6);

    while(q.size > 0) {
        printf("%f\n", dequeue(&q));
    }
    return 0;
}