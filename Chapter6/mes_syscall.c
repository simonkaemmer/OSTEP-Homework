#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

int main()
{
    struct timespec startFor, stopFor;
    struct timespec start, stop;

    int loops = 10000000;

    // For-Schleife messen
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &startFor) == 0);

    for(int i = 0; i < loops; i++) {}

    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stopFor) == 0);


    // Read messen
    /* 
        Man könnte auch die Messung in der Schleife machen, und jeden Wert aufsummieren, bei hohen Iterationen, 
        wird der Overhead nur für assert und den Aufruf von read
    */
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);

    for(int i = 0; i < loops; i++) {
        read(0, NULL, 0);
    }

    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);


    // Werte verrechnen

    double timeForLoop = (stopFor.tv_sec - startFor.tv_sec)*1000000000L + (stopFor.tv_nsec - startFor.tv_nsec);
    double timeRead = (stop.tv_sec - start.tv_sec)*1000000000L + (stop.tv_nsec - start.tv_nsec);
    double time = (timeRead - timeForLoop) / loops;

    printf("Time/Syscall: %fns\n", time);

    return 0;
}
