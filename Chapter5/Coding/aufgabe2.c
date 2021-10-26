#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <fcntl.h>
#include <wait.h>

int main()
{
    int fd = open("./aufgabe2.output", (O_RDWR|O_CREAT|O_TRUNC));
    assert(fd>=0);

    int rc = fork();

    if(rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if(rc == 0) {
        //Child
        while(1){
            write(fd, "C", strlen("C\n"));
            printf("Child ran");
        }
            
    } else {
        // Parent
        while(1) {
            write(fd, "P", strlen("C\n"));
        }
    }

    close(fd);
    return 0;
}
