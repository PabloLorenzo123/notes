#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>

// declaring
void waitExample();
void execExample(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    execExample(argc, argv);
    return 0;
}

void pipeExample(int argc, char* argv[]){
     
}

void execExample(int argc, char* argv[]) {
    if (argc != 3){
        printf("usage: ./practice file_to_read > output.txt\n");
        exit(1);
    }

    char* read_from = argv[1];
    char* save_in = argv[2];
    int child = fork();

    if (child == -1){
        printf("There was an error while trying to create a child process.\n");
        exit(1);
    }
    else if (child == 0){
        // we can cook something before calling exec.
        int of = open(save_in, O_CREAT); // CREATE FILE IF MISSING.
        close(of); // open() returns the file descriptor number.

        char* program = "wc";
        char* execArgs[] = {program, read_from, NULL};

        // trick: we want wc to output its result into a file, instead of the terminal.
        // file descriptors come into play here, these are tables that match a number to a file.
        // unix philosophy is that everything is a file, the terminal, a file, the disk..
        // wc what it does is that it writes() to whatever the file descriptor entry 1 points to.
        
        close(1); // ENTRY FOR KEY 1 IN DESCRIPTOR TABLE IS NOW FREE.
        open(save_in, O_WRONLY); // ENTRY KEY 1 NOW HAS THE FILE SET INTO THERE.

        // replace this process code with the wc.
        execvp(execArgs[0], execArgs);
    }
    else {
        wait(NULL);
        printf("wc program is done\n.");
    }
}

void waitExample() {
    printf("Hello i'm (pid: %i)\n", getpid());

    int rc = fork(); // a child process is created.
    if (rc == -1){
        printf("There was an error while trying to create a child process.\n");
        exit(1);
    }
    else if (rc == 0){
        // This work needs to be completed before parent continues execution.
        for (int i = 0; i < 100; i++){
            printf("child %i, ", i);
        }
        printf("\n");
    }
    else {
        printf("Hi i'm parent the scheduler called me, but i won't continue until child is done.\n");
        wait(NULL);

        for (int i = 0; i < 100; i++){
            printf("parent %i, ", i);
        }
        printf("\n");
    }
}