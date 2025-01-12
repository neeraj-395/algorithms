#include <stdio.h>
#include <stdlib.h>

typedef struct  node {
    double data;
    struct node *next;
} Node;

typedef struct stack {
    Node *top;
    size_t size;
} Stack;

void stack_push(Stack *s, double data) {
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = s->top;
    s->top = new_node;
    s->size = s->size + 1;
}

double stack_pop(Stack *s) {
    if(s->size == 0) return __DBL_MIN__;
    Node *tmp = s->top;
    double data  = s->top->data;
    s->top = s->top->next;
    s->size = s->size - 1;
    free(tmp);
    return data;
}

void stack_clear(Stack *s) {
    while(s->size > 0) {
        Node *tmp = s->top;
        s->top = s->top->next;
        s->size = s->size - 1;
        free(tmp);
    }
}

int main(void) {
    Stack s1 = { NULL, 0 };

    stack_push(&s1, 569);
    stack_push(&s1, 563);
    stack_push(&s1, 561);
    stack_push(&s1, 562);
    stack_push(&s1, 532);
    stack_push(&s1, 544);

    while(s1.size > 0) { printf("%f\n", stack_pop(&s1)); }
}