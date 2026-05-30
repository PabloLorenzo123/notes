#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

// Write a program that opens a file (with the open() system call)
// and then calls fork() to create a new process. Can both the child
// and parent access the file descriptor returned by open()? What
// happens when they are writing to the file concurrently, i.e., at the
// same time?

// they will both mess each other write.

int main() {
    printf("printing from terminal.\n");
    close(1);
    printf("printing from terminal.\n");
    int file = open("2.txt", O_WRONLY);
    int child = fork();

    if (child == -1){
        fprintf(stderr, "There was an error while trying to create a child process.\n");
        exit(1);
    }

    if (child == 0){
        for (int i = 0; i < 20; i++){
            printf("child\n");
        }
        close(file);
    }
    else {
        for (int i = 0; i < 50; i++){
            printf("parent\n");
        }
        close(file);
    }

    return 0;
}