#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "common.h"

/**
@param argc {int} Argument counts
@param argv {char*} pointer to a char array containing the argument values.
@returns {int} 0 if succesfull, another code otherwise.
*/
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage ./cpu_virtualization.c <string>");
        exit(1);
    }
    char *str = argv[1];

    while (1) {
        Spin(1);
        printf("%s\n", str);
    }

    return 0;
}

// IF YOU RUN  in the cmd start cpu_virt.exe pablo & cpu_virt.exe jorge you will realize
// both process run at the same time, this is called cpu virtualization.
