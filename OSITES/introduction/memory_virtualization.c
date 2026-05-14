#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv) {
    int *p = malloc(sizeof(int));

    if (p == NULL) {
        return -1;
    }

    printf("(%d) address is pointing to p: %p\n", getpid(), p);
    
    *p = 0;
    while (1) {
        Spin(1);
        *p = *p + 1;
        printf("(%d) p is point to %i\n", getpid(), *p);
    }

    return 0;
}

// If you start this program in two proccesses it's possible you may see
// that the memory address of p is the same, each program think it has
// all the memory of the machine, but in reality not. this is memory
// virtualization.