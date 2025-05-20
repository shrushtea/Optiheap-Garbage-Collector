// allocator main 

#include "allocator_fn.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// keeping track + ref count here 
typedef struct MemBlock {
    void* ptr;
    size_t ref_count;
    struct MemBlock* next;
} MemBlock;

static MemBlock* head = NULL;

// helper 
static MemBlock* find_block(void* ptr) {
    MemBlock* current = head;
    while (current) {
        if (current->ptr == ptr) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void* my_malloc(size_t size) {
    void* ptr = malloc(size);
    if (!ptr) {
        return NULL;
    }

    MemBlock* block = malloc(sizeof(MemBlock));
    if (!block) {
        free(ptr);
        return NULL;
    }

    block->ptr = ptr;
    block->ref_count = 0;
    block->next = head;
    head = block;

    return ptr;
}

void add_ref(void* ptr) {
    MemBlock* block = find_block(ptr);
    if (block) {
        block->ref_count++;
    } else {
        printf("add_ref: Pointer not found.\n");
    }
}

void release_ref(void* ptr) {
    MemBlock* block = find_block(ptr);
    if (block) {
        if (block->ref_count > 0) {
            block->ref_count--;
        }

        if (block->ref_count == 0) {
            // removing block from list
            if (head == block) {
                head = block->next;
            } else {
                MemBlock* prev = head;
                while (prev->next && prev->next != block) {
                    prev = prev->next;
                }
                if (prev->next) {
                    prev->next = block->next;
                }
            }

            free(block->ptr);
            free(block);
        }
    } else {
        printf("release_ref: Pointer not found.\n");
    }
}

void gc_collect(void) {
    MemBlock* current = head;
    MemBlock* prev = NULL;

    while (current) {
        if (current->ref_count == 0) {
            MemBlock* to_free = current;
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            current = current->next;

            free(to_free->ptr);
            free(to_free);
        } else {
            prev = current;
            current = current->next;
        }
    }
}
