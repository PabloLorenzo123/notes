#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

// Now write a program that uses wait() to wait for the child process
// to finish in the parent. What does wait() return? What happens if
// you use wait() in the child

int main()
{
    int rc = fork();

    if (rc == 0)
    {
        printf("When you say goodbye.\n");
    }

    if (rc > 1)
    {
        wait(NULL);
        printf("I say hello\n.");
    }

    return 0;
}
