#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Write a program that calls fork(). Before calling fork(),have the
// main process access a variable (e.g., x) and set its value to some
// thing (e.g., 100). What value is the variable in the child process?
// What happens to the variable when both the child and parent change
// the value of x?

// 1 - the child variable will read the correct value of x, because the parent stack was copied.
// 2 - the only affect their local variable.
int main(){
    int x = 100;

    int child = fork();
    if (child == -1){
        fprintf(stderr, "There was an error trying to create a child process.\n");
        exit(1);
    }

    if (child == 0){
        x -= 200;
        printf("I'm the child process, variable x = %i\n", x);
    }
    else {
        // parent code.
        x += 5;
        printf("I'm the parent process, vairable x = %i\n", x);
    }

    return 0;
}
