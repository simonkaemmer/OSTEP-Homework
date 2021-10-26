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
    int wstatus; // Ausgabe, in welchem Status das Kind steht bzw. stand

    if(rc < 0) {
        fprintf(stderr, "fork failed\n");

    } else if(rc == 0) {
        // Child
        printf("\nHello!\n");

    } else {
        // Parent
        waitpid(-1, &wstatus, 0);
        printf("Bye!\n");
    }

    printf("Child status: %d\n", wstatus);
    return 0;
}
