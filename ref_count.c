#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ref_count;
    void *pointer;
} ObjectRef;

ObjectRef* makeRef(void *pointer) {
    ObjectRef *obj = malloc(sizeof(ObjectRef));
    if (obj) {
        obj->ref_count = 1;
        obj->pointer = pointer;
    }
    return obj;
}

void increment(ObjectRef *obj) {
    if (obj) {
        obj->ref_count = obj->ref_count + 1;
    }
}

void decrement(ObjectRef *obj) {
    if (obj) {
        obj->ref_count = obj->ref_count - 1;
        if (obj->ref_count == 0) {
            free(obj->pointer);
            free(obj);
        }
    }
}

void* getData(ObjectRef *obj) {
    if (obj) {
        return obj->pointer;
    }
    return NULL;
}

int main() {
    int *number = malloc(sizeof(int));
    *number = 50;
    
    ObjectRef *myRef = makeRef(number);
    
    int *value = getData(myRef);
    printf("The value is: %d\n", *value);
    
    increment(myRef);
    printf("Reference count: %d\n", myRef->ref_count);
    
    decrement(myRef);
    decrement(myRef);
    
    return 0;
  
}
