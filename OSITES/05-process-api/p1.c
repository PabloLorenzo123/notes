#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("hello world (pid: %i)\n", getpid());
    int rc = fork(); // The kernel will create a copy of the running processes, including copying the pc register.
    // this fork() will return 1 or -1 for the parent process, and 0 for the child process.
    if (rc == -1){
        printf("There was an error trying to create a child process.\n");
        exit(1);
    }
    else if (rc == 0){
        printf("hello, i am child (pid: %i)\n", getpid());
    }
    else {
        printf("hello, i am parent of %i (pid:%i)\n", rc, getpid());
    }
    return 0;
}
