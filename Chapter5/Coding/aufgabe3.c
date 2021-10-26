#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

int main()
{
    pid_t rc = fork();
    //int fd = open("./aufgabe3.output", (O_RDWR|O_CREAT|O_TRUNC));

    if(rc < 0) {
        fprintf(stderr, "fork failed\n");

    } else if(rc == 0) {
        // Child
        printf("\nHello!\n");
        //kill(getpid(), SIGTERM);
        kill(getppid(), 18); //Sende Sigcont an den Elternprozess
    } else {
        // Parent
        kill(getpid(), 20); //Sende Sigstop an den Elternprozess
        //while(kill(rc, 0) == 0);
        printf("\nGoodbye!\n");
    }
    return 0;
}
