#include "hashmap.h"

void destroy(Object *obj) { free(obj->data); }

int main(void) {

    Hashmap map = hmap_create(10);

    int a = 5, b = 3, c = 7; 
    int *d = malloc(sizeof(int)); *d = 395;

    Object obj1 = object_create(&a, sizeof(a), sizeof(int), NULL);
    Object obj2 = object_create(&b, sizeof(b), sizeof(int), NULL);
    Object obj3 = object_create(&c, sizeof(c), sizeof(int), NULL);
    Object obj4 = object_create(d, sizeof(d), sizeof(int *), destroy);

    hmap_insert(&map, "Neeraj", &obj1);
    hmap_insert(&map, "Rahul", &obj2);
    hmap_insert(&map, "Priyanshu", &obj3);
    hmap_insert(&map, "Sudhanshu", &obj4);

    hmap_show(&map);

    Object *result = hmap_lookup(&map, "Sudhanshu");

    if(result) printf("lookup result: %d\n", objcast(result, int)[0]);
    
    hmap_free(&map);

    return 0;
}