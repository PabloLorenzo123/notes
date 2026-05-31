#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Write a program that calls fork() and then calls some form of
// exec() to run the program /bin/ls. See if you can try all of the
// variants of exec(),including execl(), execle(), execlp(),
// execv(), execvp(), and execvP(). Why do you think there
// are so many variants of the same basic call?

// The most essential exec is execve() the others are wrapped around it.
// v -> vector (expects an array as the programs arguments)
// e -> can configure different environment variables, by default it copies the parent environment variables.
// p -> search also in PATH when executing the program, so you can pass ls instead of /bin/ls for instance.
// execvp(char* program, char* args[]);
// execvpe(char* program, char* args[], char *envp[]);
// execlp(char* program, char* first_param, char* second_param, ...);
// execl(char* program, char* first_param, char* second_param, ...);
// execle(char* program, char* first_param, char* scond_param, char *envp[]);
// execvP() is not part of POSIX.

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