#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main()
{
    struct array arr = {.data = (int *) malloc(sizeof(int)), .size=sizeof(int)};
    arr.data[0] = 1;

    struct array *arr_ptr = &arr;

    arrayAddElement(arr_ptr, 3);
    arrayAddElement(arr_ptr, 4);


    printf("Data:%d \n", arr.data[0]);
    printf("Data:%d \n", arr.data[1]);
    printf("Data:%d \n", arr.data[2]);

    arrayDelete(arr_ptr);

    return 0;
}



