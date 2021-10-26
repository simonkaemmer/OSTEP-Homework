#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

int main()
{
    int x = 100;

    int rc = fork();
    assert(rc >= 0);

    if(rc == 0) {
        x = x+1;
        printf("Child with PID: %d x: %d\n", (int) getpid(), x);
    } else {
        
        x = x + 1;
        printf("Parent with PID %d x: %d\n", (int) getpid(), x);
    }

    return 0;
}
