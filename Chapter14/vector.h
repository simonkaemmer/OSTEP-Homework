#include <stdio.h>
#include <stdlib.h>


struct array {
    int * data; 
    int size;
};

void arrayAddElement(struct array *arr, int value) {
    
    arr->data = (int*) realloc(arr->data, arr->size + sizeof(int));
    arr->size += sizeof(int);
    arr->data[(arr->size/sizeof(int)) - 1] = value;
}

void arrayDelete(struct array *arr) {
    arr->size = 0;
    free(arr->data);
}