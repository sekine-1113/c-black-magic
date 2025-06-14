#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Object;
struct _VTable {
    void (*print)(struct _Object* self);
    void (*destroy)(struct _Object* self);
    size_t (*length)(struct _Object* self);
};
typedef struct _VTable VTable;

struct _Object {
    VTable* vtable;
};
typedef struct _Object Object;

struct _String {
    Object base;
    char* value;
};
typedef struct _String String;
void print_string(Object* self);
void destroy_string(Object* self);
size_t length_string(Object* self);
static VTable string_VTable = { print_string, destroy_string, length_string, };
String* new_String(char* value);

struct _Integer {
    Object base;
    int value;
};
typedef struct _Integer Integer;
void print_integer(Object* self);
void destroy_integer(Object* self);
static VTable integer_VTable = { print_integer, destroy_integer, NULL, };
Integer* new_Integer(int value);

void print(Object* obj) {
    if (obj && obj->vtable && obj->vtable->print) {
        obj->vtable->print(obj);
    }
}
void delete(Object* obj) {
    if (obj) {
        if (obj->vtable && obj->vtable->destroy) {
            obj->vtable->destroy(obj);
        }
        free(obj);
    }
}
size_t len(Object* obj) {
    if (obj && obj->vtable && obj->vtable->length) {
        return obj->vtable->length(obj);
    }
    return 0;
}

int main(void) {
    Object* objects[2];
    objects[0] = (Object*)new_String("Hello, World!");
    objects[1] = (Object*)new_Integer(1234);

    for (int i=0; i<2; i++) {
        print(objects[i]);
        printf("len = %ld\n", len(objects[i]));
    }

    for (int i=0; i<2; i++) {
        delete(objects[i]);
    }
    return 0;
}

// char* strdup(const char* str) {
//     size_t len = strlen(str);
//     char* dup = (char*)malloc(len + 1);
//     strcpy(dup, str);
//     return dup;
// }

void destroy_string(Object* self) {
    String* obj = (String*)self;
    free(obj->value);
}
void print_string(Object* self) {
    String* obj = (String*)self;
    printf("%s\n", obj->value);
}
size_t length_string(Object* self) {
    String* obj = (String*)self;
    return strlen(obj->value);
}
String* new_String(char* value) {
    String* obj = (String*)malloc(sizeof(String));
    obj->base.vtable = &string_VTable;
    obj->value = strdup(value);
    return obj;
}


void print_integer(Object* self) {
    Integer* obj = (Integer*)self;
    printf("%d\n", obj->value);
}
void destroy_integer(Object* self) {}
Integer* new_Integer(int value) {
    Integer* obj = (Integer*)malloc(sizeof(Integer));
    obj->base.vtable = &integer_VTable;
    obj->value = value;
    return obj;
}
