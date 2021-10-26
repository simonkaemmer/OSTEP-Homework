#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <wait.h>

int main()
{
    pid_t rc = fork();

    if(rc < 0) {
        fprintf(stderr, "fork failed\n");

    } else if(rc == 0) {
        // Child
        close(STDOUT_FILENO);
        printf("\nHello!\n");

    } else {
        // Parent
        wait(NULL);
        printf("\nGoodbye!\n");
    }
    return 0;
}
