#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct __node {
    void *data;
    size_t size;
    struct __node *next;
} Node;

typedef struct __list {
    Node *head;
    Node *tail;
    size_t length;
} List;

void list_append(List *list, const void *data, size_t bytes) {
    Node *new = (Node *)malloc(sizeof(Node));
    new->data = malloc(bytes);
    memcpy(new->data, data, bytes);
    if(list->head == NULL) {
        list->head = new;
        list->tail = new;
    } else {
        list->tail->next = new;
        list->tail = new;
    }
    list->length++;
}

void list_remove(List *list, size_t index) {
    if(!list || !list->head) return;
    if(index >= list->length) return;
    Node *curr = list->head, *prev = NULL;

    for(size_t i = 0; i < index; i++) {
        prev = curr;
        curr = curr->next;
    }

    if(prev) prev->next = curr->next;
    else list->head = curr->next;

    free(curr->data);
    free(curr);
    list->length--;
}

void list_clear(List *list) {
    if(!list || !list->head) return;
    Node *node = list->head;
    while(node != NULL) {
        list->head = node->next;
        free(node->data);
        free(node);
        list->length--;
        node = list->head;
    } 
    list->head = NULL;
    list->tail = NULL;
}

int main(void) {

    List l1 = {NULL, NULL, 0};
    int a = 5, b = 6, c = 56;

    list_append(&l1, &a, sizeof(int));
    list_append(&l1, &b, sizeof(int));
    list_append(&l1, &c, sizeof(int));

    printf("list size: %ld\n", l1.length);
    printf("%d\n", *(int *)l1.head->data);
    printf("%d\n", *(int *)l1.head->next->data);
    printf("%d\n", *(int *)l1.tail->data);

    list_clear(&l1);

    return 0;
}