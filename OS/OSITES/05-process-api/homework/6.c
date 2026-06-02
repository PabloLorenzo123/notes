#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Write a slight modification of the previous program, this time us
// ing waitpid() instead of wait(). When would waitpid() be
// useful? waitpid would be useful when we have multiple child processes and we want to wait on only one of them.

int main()
{
    int rc = fork();

    if (rc == 0)
    {
        printf("When you say goodbye.\n");
    }

    if (rc > 1)
    {
        waitpid(rc, NULL, 0);
        printf("I say hello\n.");
    }

    return 0;
}
