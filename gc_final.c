#include "allocator_fn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void show_menu() {
    printf("\n--- Memory Manager Menu ---\n");
    printf("1. Create new array\n");
    printf("2. Delete array\n");
    printf("3. Run Garbage Collector\n");
    printf("4. Quit program\n");
    printf("What do you want to do? ");
}

int main() {
    void *my_array = NULL;
    int choice;
    size_t array_size = 0;
    
    printf("Welcome to My Memory Manager Program\n");
    
    while(1) {
        show_menu();
        
        if (scanf("%d", &choice) != 1) {
            printf("Error: please enter a number\n");

            while(getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 1:
                if (my_array != NULL) {
                    printf("Array already exists! Delete it first.\n");
                    break;
                }
                
                printf("How big should the array be? ");
                if (scanf("%zu", &array_size) != 1 || array_size == 0) {
                    printf("Error: invalid size\n");
                    break;
                }
                
                my_array = my_malloc(array_size * sizeof(int));
                if (my_array == NULL) {
                    printf("Could not create array :(\n");
                } else {
                    printf("Array created at address %p\n", my_array);
                    add_ref(my_array);  
                }
                break;
                
            case 2:
                if (my_array != NULL) {
                    release_ref(my_array);  
                    my_array = NULL;
                    printf("Array deleted!\n");
                } else {
                    printf("No array to delete!\n");
                }
                break;
                
            case 3:
                printf("Starting garbage collection.\n");
                gc_collect();
                printf("Garbage collection finished!!\n");
                break;
                
            case 4:
                printf("Exiting program...\n");
                if (my_array != NULL) {
                    release_ref(my_array);
                    my_array = NULL;
                }
                gc_collect();
                return 0;
                
            default:
                printf("You're not funny. Enter something between 1-4 only.\n");
                break;
        }
    }
    
    return 0;
}
