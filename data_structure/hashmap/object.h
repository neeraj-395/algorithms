#ifndef OBJECT_H
#define OBJECT_H

#define objcast(obj,type) ((type *)obj.data)

typedef struct _object {
    const void *data;
    unsigned short size;
    unsigned short length;
} Object;
 
Object object_create(void *data, unsigned bytes, unsigned size) {
    return (Object) { .data = data, .size = size, .length = bytes / size};
}

#endif // OBJECT_H