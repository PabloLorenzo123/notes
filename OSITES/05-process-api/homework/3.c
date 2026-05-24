#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Write another program using fork(). The child process should
// print “hello”; the parentprocessshouldprint“goodbye”. Youshould
// try to ensure that the child process always prints first; can you do
// this without calling wait() in the parent?

// no i can't be done without wait() because this would require that these proccesses
// share a variable, which they can't. unless we're using IPC. i'm wrong, we could use a file to save the state.

int main() {
    int rc = fork();
    if (rc == -1){
        fprintf(stderr, "There was an error while trying to create a child process.\n");
        exit(1);
    }

    if (rc == 0){
        printf("hello.\n");
    }
    else {
        wait(NULL);
        printf("goodbye\n");
    }

    return 0;
}
