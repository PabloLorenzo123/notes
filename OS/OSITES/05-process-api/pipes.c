#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

// To demonstrate pipes, let's create a program what from the current directory files
// filter files with a certain name, using the built-in unix functions.
// using ls and wc which are standard POSIX utilities that POSIX compliant operating systems are expected to provide.
// ls and wc are part of the POSIX userland utilities, not kernel featurres.
// POSIX (Portable Operating System Interface) and the X -> UNIX. POSIX defines both userland utilities (cat, ls, wc) and System intercaes (open, read, write, close, fork).
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./pipes [folder_file_name_to_look_for].\n");
        exit(1);
    }
    char *word = argv[1];

    int fd[2];
    // pipe will add at index 0, a read-end, and at index 1 a write-end. these numerical values will represent
    // file descriptors.
    pipe(fd);

    // now i create a copy of this process, (pc, stack, static code, and most importantingly file descriptors).
    pid_t lschild = fork();

    if (lschild == 0) // child goes here.
    {
        // still unclear why we need to close this, but suppose now that its because we won't use this.
        close(fd[0]);
        // close(STDOUT_FILENO); // let's close the output file descriptor, which at this point is the terminal.
        // fopen(fd[1]);         // now the descriptor for this will be the 1 (output), ls will print to this fd[1].
        dup2(fd[1], STDOUT_FILENO); // this will put fd[1] in the descriptor of STDOUT_FILE.

        char *args[] = {"ls", NULL};
        execvp("ls", args);

        // if exec is succesful, remember the the process code is all overwritten, so these lines would never execute.
        perror("execvp ls");
        exit(1);
    }

    // parent will wait for ls to be done.
    waitpid(lschild, NULL, 0);

    // now let's run wc.
    pid_t wcchild = fork();

    if (wcchild == 0)
    {                 // it's the child process running here.
        close(fd[1]); // this process won't write. it's important to close it because read(fd[0]) will only return EOF, when all fd[1] are closed.
        // close(STDIN_FILEIN); // close reading descriptor.
        // open(fd[0]);         // what ls buffered up, can now be read here.
        dup2(fd[0], STDIN_FILENO);

        char *params[] = {word, NULL};
        execvp("wc", params);

        // if exec is succesful, remember the the process code is all overwritten, so these lines would never execute.
        perror("wc");
        exit(1);
    }

    
    close(fd[0]);
    close(fd[1]); // if we omit this, this program will run forever, because wc the reader will never get the EOF.

    waitpid(wcchild, NULL, 0);

    return 0;
}
