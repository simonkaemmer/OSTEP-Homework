#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

#define mebibytes (1024*1024)

int main(int argc, char const *argv[])
{    
    if(argc != 3){
        fprintf(stderr, "./mem-user MemToUse TimeForRun\n");
        exit(EXIT_FAILURE);
    }

    struct timespec start, stop;

    long size = atoi(argv[1]) * mebibytes;
    long runtime = atoi(argv[2]);

    char *array = (char *) malloc(size);

    printf("PID for pmap: %d\n", getpid());

    for(int i = 0; i < size; i++){
        array[i] = 'a';
    }

    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);

    for(int i = 0; 1; i++) {

        if(i%100 == 0) {
            assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);

            if(runtime <= (stop.tv_sec - start.tv_sec)) {
                break;
            }
        }

        if(i == size-1) {
            i = 0;
        }

        array[i] += 1;
    }
    
    free(array);
    return 0;
}
