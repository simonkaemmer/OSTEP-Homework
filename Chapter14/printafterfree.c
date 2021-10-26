#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    //int *data = (int*) calloc(0, 100*sizeof(int));
    int *data = (int*) malloc(100*sizeof(int));

    for(int i = 0; i < 400; i++) {
        data[i] = 1;
    }

    free(data);
    printf("Try to print: %d\n", data[99]);
    return 0;
}
