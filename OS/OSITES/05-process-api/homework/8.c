#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1

// 8. Write a program that creates two children, and connects the stan
// dard output of one to the standard input of the other, using the
// pipe() system call

// this program count the number of files in the current directory.
int main()
{
    int fd[2];
    if (pipe(fd) == -1)
    {
        perror("Could not create pipe.\n");
        exit(1);
    }

    pid_t ch1 = fork();
    pid_t ch2 = fork();

    if (ch1 == 0)
    {
        close(fd[READ_END]);

        dup2(fd[WRITE_END], STDOUT_FILENO);
        char *args[] = {"ls", NULL};

        execvp(args[0], args);
    }

    if (ch2 == 0)
    {
        close(fd[WRITE_END]);

        dup2(fd[READ_END], STDIN_FILENO);

        char *args[] = {"wc", "-l",  NULL};

        execvp(args[0], args);
    }

    close(fd[READ_END]);
    close(fd[WRITE_END]);

    waitpid(ch1, NULL, 0);
    waitpid(ch2, NULL, 0);

    return 0;
}
