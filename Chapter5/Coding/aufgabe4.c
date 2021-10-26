#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    pid_t rc = fork();

    if(rc < 0) {
        fprintf(stderr, "fork failed");
    } else if(rc == 0) {
        // Child

        char *args[2];
        args[0] = strdup("ls");       //1
        //args[0] = strdup("/bin/ls");  //2
        args[1] = NULL;

        //execvp(args[0], args);        //1
        //execl(args[0], "", NULL);     //2
        //execle(args[0], "", (char*) NULL, NULL); //2 letzter Parameter für Umgebungsvariable
        //execlp(args[0], "", NULL); //1 
        //execv(args[0], args); //2
        execvpe(args[0], args, NULL); // 1
    } else {
        // Parent
        wait(NULL);
    }
    return 0;
}
