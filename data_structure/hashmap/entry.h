#ifndef ENTRY_H
#define ENTRY_H

#include <stdlib.h>

#include "object.h"

typedef struct _entry {
    char *key;
    Object value;
    struct _entry *next;
} Entry;

void entry_append(Entry *e, const char *key, const Object value) {
    if(!e) return;

    // Traverse to the end of the entry list
    Entry *temp = e;
    while(temp->next) temp = temp->next;

    // Create a new entry!
    Entry *new = (Entry *)malloc(sizeof(Entry));
    new->key = strdup(key);
    new->value = value;
    new->next = NULL;

    // Append the new entry to the end of entry list;
    temp->next = new;
}

void entry_destroy(Entry *e) {
    if(!e) return;

    while(e->next) {
        Entry *temp = e->next;
        if(temp->key) free(temp->key);
        free(temp);
        e->next = e->next->next;
    }
}

#endif // ENTRY_H