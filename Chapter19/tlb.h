// tlb.h - Adrian Weishaupt, Simon Kaemmer - Gruppe 29

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>

#define BILLION 1000000000

// Function to calculate timedifference from stop to start with overflow handling
long calcTime(struct timespec start, struct timespec stop, int loops) {

    struct timespec res;
    // Check if nsec gets negative, and correct it
    if((stop.tv_nsec - start.tv_nsec) < 0) {
        res.tv_sec = stop.tv_sec - start.tv_sec -1; // Correct addition of 1Bil nanosecs
        res.tv_nsec = stop.tv_nsec - start.tv_nsec + BILLION;
    } else {
        res.tv_sec = stop.tv_sec - start.tv_sec;
        res.tv_nsec = stop.tv_nsec - start.tv_nsec;
    }

    return ((res.tv_sec * BILLION + res.tv_nsec) / loops);
}

// Function to measure TLB-Paging
long measurePaging(long PAGESIZE, int NUMPAGES, int LOOPS) {

    struct timespec start, stop;

    // Array to loop through
    int *array = (int*) malloc(NUMPAGES * PAGESIZE);
    int jump = PAGESIZE / sizeof(int);

    for(int i = 0; i < NUMPAGES * jump; i += jump) { // Preinit for array
        array[i] = 0;
    }

    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &start) == 0);
    for(int i = 0; i < LOOPS; i++) {

        for(int j = 0; j < NUMPAGES * jump; j += jump) {

            array[j] += 1;
        }
    }
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stop) == 0);


    free(array);
    return calcTime(start, stop, LOOPS*NUMPAGES);
}

long measureOverhead(int loops, int numpages) {

    struct timespec startBothFor, stopBothFor;

    // Measure Both Loops
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &startBothFor) == 0);
    for(int i = 0; i < loops; i++){
        for(int j = 0; j < numpages; j++){}
    }
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stopBothFor) == 0);

    long timeBothLoops = calcTime(startBothFor, stopBothFor, loops*numpages);

    return timeBothLoops;
}

