#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Write a program that calls fork() and then calls some form of
// exec() to run the program /bin/ls. See if you can try all of the
// variants of exec(),including execl(), execle(), execlp(),
// execv(), execvp(), and execvP(). Why do you think there
// are so many variants of the same basic call?

int main(){
    int rc = fork();
    if (rc == -1){
        fprintf(stderr, "There was an error while trying to create a child process.\n");
        exit(1);
    }

    if (rc == 0){
        // char* program = "/bin/ls";
        // int status = execl(program, program, NULL);
        // if (status == -1){
        //     fprintf(stderr, "could not execute the ls program.\n");
        //     exit(1);
        // }
    }

    return 0;
}