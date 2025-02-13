#include "hashmap.h"

int main(void) {

    Hashmap map = hmap_create(10);

    int a = 5, b = 3, c = 7;

    Object obj1 = object_create(&a, sizeof(a), sizeof(int));
    Object obj2 = object_create(&b, sizeof(b), sizeof(int));
    Object obj3 = object_create(&c, sizeof(c), sizeof(int));

    hmap_insert(&map, "Neeraj", obj1);
    hmap_insert(&map, "Singh", obj2);
    hmap_insert(&map, "Kumar", obj3);

    hmap_show(&map);

    Object result = hmap_lookup(&map, "Singh");

    printf("lookup result: %d\n", objcast(obj1, int)[0]);
    
    hmap_free(&map);

    return 0;
}