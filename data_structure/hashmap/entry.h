#ifndef ENTRY_H
#define ENTRY_H

#include <stdlib.h>

#include "object.h"

typedef struct entry {
    char *key;          // The key associated with the entry.
    Object *value;      // A pointer to the value associated with the entry.
    struct entry *next; // A pointer to the next entry in the entry list.
} Entry;

void entry_append(Entry *e, const char *key, Object *value) {
    if(!e) return;

    // Traverse to the end of the entry list
    Entry *temp = e;
    while(temp->next) temp = temp->next;

    // Create a new entry!
    Entry *new = (Entry *)malloc(sizeof(Entry));
    new->key = strdup(key);
    new->value = value;
    new->next = NULL;

    // Append the new entry to the end of entry list
    temp->next = new;
}

void entry_destroy(Entry *entry) {
    // loop over the entire linked list and free memory for each entry
    while(entry) {
        Entry *tmp = entry; // save the current entry to free it later
        entry = entry->next; // move to the next entry in the entry list

        if(tmp->key) free(tmp->key);

        // call the object destructor to free the object data
        if(tmp->value->delete) {
            tmp->value->delete(tmp->value);
        } free(tmp);
    }
}

#endif // ENTRY_H