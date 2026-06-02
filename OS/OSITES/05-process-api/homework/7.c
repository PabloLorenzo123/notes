#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 7. Write a program that creates a child process, and then in the child
// closes standardoutput(STDOUT
// FILENO).Whathappensifthechild
// calls printf() to print some output after closing the descriptor?
// no where, there's nothing in that file descriptor. the message won't be printed.

int main()
{
    pid_t rc = fork();

    if (rc == 0)
    {
        close(STDOUT_FILENO);
        printf("Where will this go?\n.");
    }

    return 0;
}