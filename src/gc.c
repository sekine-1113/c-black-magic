#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define gc_alloc_safe(val, type) gc_alloc(&(type){val}, sizeof(type), free)
#define gc_alloc_array_safe(arr, len, type) gc_alloc((arr), sizeof(type) * (len), free)

typedef void (*Finalizer)(void*);

struct GCObject {
    void* object;
    int count;
    Finalizer finalizer;
};

typedef struct GCObject GCObject;

GCObject* GC[100];
unsigned int GC_COUNT = 0;

GCObject* _gc_alloc(void* value, Finalizer finalizer) {
    GCObject* obj = (GCObject*)malloc(sizeof(GCObject));
    if (!obj) return NULL;
    obj->object = value;
    obj->count = 1;
    obj->finalizer = finalizer;
    GC[GC_COUNT++] = obj;
    return obj;
}

GCObject* gc_alloc(void* value, size_t size, Finalizer finalizer) {
    void* ptr = malloc(size);
    if (!ptr) return NULL;
    memcpy(ptr, value, size);
    return _gc_alloc(ptr, finalizer);
}

GCObject* gc_incr(GCObject* obj) {
    if (obj == NULL) return NULL;
    obj->count++;
    return obj;
}

GCObject* gc_decr(GCObject* obj) {
    if (obj == NULL) return NULL;
    if (obj->count > 0) obj->count--;
    if (obj->count <= 0) {
        int found_index = -1;
        for (int i=0; i<GC_COUNT; i++) {
            if (GC[i] == obj) {
                if (obj->finalizer != NULL) {
                    obj->finalizer(obj->object);
                }
                free(obj);
                found_index = i;
            }
        }
        if (found_index != -1) {
            for (int i=found_index; i<GC_COUNT; i++) {
                GC[i] = GC[i+1];
            }
            GC_COUNT--;
        }
        return NULL;
    }
    return obj;
}

void* gc_ref(GCObject* obj) {
    return obj ? obj->object : NULL;
}

void gc_cleanup(void) {
    for (int i=0; i<GC_COUNT; i++) {
        if (GC[i]->finalizer != NULL) {
            GC[i]->finalizer(GC[i]->object);
        }
        free(GC[i]);
    }
    GC_COUNT = 0;
}

int main(void) {
    GCObject* hello = gc_alloc((char*)"Hello", sizeof("Hello"), NULL);
    printf("hello = %s\n", (char*)gc_ref(hello));

    GCObject* num = gc_alloc_safe(100, int);
    printf("num = %d\n", *(int*)gc_ref(num));

    int data[] = {1, 2, 3, 4, 5};
    GCObject* array = gc_alloc_array_safe(data, 5, int);
    int *ref_data = (int*)gc_ref(array);
    for (int i=0; i<5; i++) {
        printf("%d ", *(ref_data+i));
    }
    printf("\n");

    gc_cleanup();
    return 0;
}
