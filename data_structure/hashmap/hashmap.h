#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <string.h>

#include "entry.h"

typedef struct _hashmap {
    Entry *entries;
    unsigned length;
} Hashmap;

unsigned long hash(const char *str, unsigned range) {
    int i = 0; unsigned long hash = 5381;
    while(str[i] != '\0') hash = ((hash << 5) + hash) + str[i++];
    return hash % range;
}

Hashmap hmap_create(unsigned num_entries) {
    return (Hashmap) {
        .entries = calloc(num_entries, sizeof(Entry)),
        .length = num_entries
    };
}

void hmap_insert(Hashmap *map, const char *key, Object value) {
    unsigned long index = hash(key, map->length);
    entry_append(&map->entries[index], key, value);
}

Object hmap_lookup(Hashmap *map, const char *key) {
    if(!map && !map->entries) return (Object) {NULL, 0 , 0};
    unsigned long index = hash(key, map->length);

    Entry *curr = map->entries[index].next;

    while(curr != NULL) {
        if(strcmp(curr->key, key) == 0) {
            return curr->value;
        } curr = curr->next;
    } return (Object) {NULL, 0, 0};
}

void hmap_free(Hashmap *map) {
    if(!map && !map->entries) return;
    for(int i=0; i < map->length; i++) {
        entry_destroy(&map->entries[i]);
    } free(map->entries);
}

void hmap_show(Hashmap *map) {
    if(!map && !map->entries) return;
    for(int i = 0; i < map->length; i++) {
        Entry *tmp = map->entries[i].next;
        if(!tmp) continue;
        printf("[%d] value: %p, key: %s, next: %p\n", 
                 i, &tmp->value, tmp->key, tmp->next);
    }
}


#endif // HASHMAP_H