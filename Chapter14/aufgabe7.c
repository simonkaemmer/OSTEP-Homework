#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *data = (int*) malloc(100*sizeof(int));
    int *ptr = &data[50];
    free(ptr);
    return 0;
}
