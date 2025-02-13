#ifndef OBJECT_H
#define OBJECT_H

#define objcast(obj,type) ((type *)obj->data)

typedef struct _object Object;
typedef void (*obj_destructor)(Object *obj);

typedef struct _object {
    void *data;
    unsigned short size;
    unsigned short length;
    obj_destructor delete;
} Object;
 
Object object_create(void *data, unsigned bytes, unsigned size, obj_destructor func) {
    return (Object) { .data = data, .size = size, .length = bytes / size, .delete = func};
}

#endif // OBJECT_H