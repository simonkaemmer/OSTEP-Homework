#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>

int main()
{
    int fd[2];

    assert(pipe(fd) == 0);

    pid_t child1 = fork();

    if(child1 < 0) {
        fprintf(stderr, "fork failed\n");

    } else if(child1 == 0) {
        // Child1
        close(fd[0]); // Leseende der Pipe für Child1 schließen
        dup2(fd[1], 1); // STD_OUT auf das schreibende der Pipe kopieren

        printf("Hallo ich bin Kind 1\n");

    } else {
        // Parent
        wait(NULL); // Auf das Schreiben in die Pipe von Kind 1 warten

        pid_t child2 = fork();

        if(child2 < 0) {
        fprintf(stderr, "fork failed\n");

        } else if(child2 == 0) {

            // Child2
            close(fd[1]); // Schreibende der Pipe für Kind 2 schließen
            dup2(fd[0], 0); // STD_IN auf Leseende der Pipe kopieren
            printf("Kind 2 läuft \n");
        
            char buffer[22];
            read(STDIN_FILENO, buffer, 22);

            printf("In meinem STD_IN steht: %s", buffer);
        }
    }
    return 0;
}