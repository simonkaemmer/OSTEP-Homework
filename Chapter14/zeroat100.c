#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    int *data = (int*) malloc(100*sizeof(int));
    data[100] = 0;
    free(data);
    return 0;
}
