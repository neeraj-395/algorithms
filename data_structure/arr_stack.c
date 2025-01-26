#include <stdio.h>
#include <stdlib.h>
#define NAN (__builtin_nanf (""))

typedef struct stack {
    double *stack;
    int top;
    size_t size;
    size_t capacity;
} Stack;

Stack stack_init(size_t capacity) {
    return (Stack){
        .stack = malloc(capacity * sizeof(double)),
        .top = -1,
        .size = 0,
        .capacity = capacity
    };
}

void stack_push(Stack *s, double value) {
    if(s->capacity == s->size) {
        printf("Error: Stack is Full!!\n");
        return;
    }
    s->stack[++s->top] = value;
    s->size++;
}

double stack_pop(Stack *s) {
    if(s->size == 0) {
        printf("Error: Stack is Empty!!\n");
        return NAN;
    }
    double value = s->stack[s->top--];
    s->size--; return value;
}

void stack_clear(Stack *s) { s->top = -1; s->size = 0; }

void stack_destroy(Stack *s) {
    free(s->stack);
    s->stack = NULL;
    s->top = -1;
    s->size = 0;
    s->capacity = 0;
}

int main(void) {

    Stack s = stack_init(2);

    stack_push(&s, 10.5);
    stack_push(&s, 20.5);
    stack_push(&s, 30.5);

    printf("Popped value: %.2f\n", stack_pop(&s));
    printf("Popped value: %.2f\n", stack_pop(&s));

    stack_clear(&s);

    stack_push(&s, 40.5);

    printf("Popped value: %.2f\n", stack_pop(&s));

    stack_destroy(&s);

    return 0;
}