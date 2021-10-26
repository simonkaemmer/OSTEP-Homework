#define _GNU_SOURCE

#include <sched.h>
#include <stdio.h>
#include <sys/sysinfo.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <wait.h>

int main()
{
    struct timespec startFor, stopFor;
    struct timespec startCs, stopCs;

    int loops = 1000000;

    // Prozessoren verfügbar?
    int procs = get_nprocs();
    printf("Procs: %d\n", procs);


    // Pipe für die richtige Messung
    int pipe1[2];
    int pipe2[2];

    // Pipe für die Overhead-Messung
    int testPipe[2];

    assert(pipe(pipe1) == 0);
    assert(pipe(pipe2) == 0);
    assert(pipe(testPipe) == 0);

    // Overhead von write/read, und der For-Schleife messen

    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &startFor) == 0);

    for(int i = 0; i < loops; i++) {
        write(testPipe[1], NULL, 0);
        read(testPipe[0], NULL, 0);
    }
    
    assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stopFor) == 0);

    double timeForNsec = stopFor.tv_nsec - startFor.tv_nsec;
    if(timeForNsec < 0) {
        timeForNsec = timeForNsec + 1000000000;
    }

    double timeFor = ((stopFor.tv_sec - startFor.tv_sec)*100000000 + timeForNsec)/loops; // Zeit die es für alles außer die Context-Switche braucht

    pid_t rc = fork();

    if(rc < 0) {
        fprintf(stderr, "Forking failed");
    } else if( rc == 0) {
        // Child

        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(procs -1, &mask);
        sched_setaffinity(0, sizeof(cpu_set_t), &mask);

        for(int i = 0; i<loops; i++) {
            read(pipe2[0], NULL, 0);
            write(pipe1[1], NULL, 0);
        }

    } else {
        // Parent

        cpu_set_t mask;
        CPU_ZERO(&mask);
        CPU_SET(procs - 1, &mask);
        sched_setaffinity(0, sizeof(cpu_set_t), &mask);

        assert(clock_gettime(CLOCK_MONOTONIC_RAW, &startCs) == 0);
        for(int i = 0; i<loops; i++) {
            write(pipe2[1], NULL, 0);
            read(pipe1[0], NULL, 0);
        }
        assert(clock_gettime(CLOCK_MONOTONIC_RAW, &stopCs) == 0);

        double timeCsNsec = (stopCs.tv_nsec - startCs.tv_nsec);

        // Correction falls nsec negativ wird
        if(timeCsNsec<0) {
            timeCsNsec = timeCsNsec + 1000000000;
        }

        double timeAll = ((stopCs.tv_sec - startCs.tv_sec)*1000000000 + timeCsNsec)/loops - timeFor;
        printf("Time for one context-switch: %fns\n", timeAll / 2); // geteilt durch zwei, weil ja einmal hin, und wieder zurück geswitcht wird
    }
    return 0;
}
