#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common.h"

volatile int counter = 0;
int loops;

// This method will be run by each thread.
// think of a thread as a process with the same address space
// of at least one other process. Threads are used to do work concurrently.
// author words: a thread can be seen as a function running in the same address space
// as other functions, with more than one of them active at a time.
void* worker(void* args) {
    int i;
    for (i = 0; i < loops; i++) {
        counter++;
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("usage: threads <value>\n");
        exit(1);
    }

    loops = atoi(argv[1]);
    pthread_t p1; // variable that represents a thread. it holds the reference to a thread, similar to a process id but for threads.
    pthread_t p2;

    printf("counter initial value: %i\n", counter);
    // Create a thread
    pthread_create(
        &p1, // save the identifier of the thread in this address.
        NULL, // thread settings.
        worker, // function the thread will run.
        NULL    // addresses of the arguments for the worker function.
    );

    pthread_create(
        &p2,
        NULL,
        worker,
        NULL
    );

    // Wait for threads to execute their work.
    // If number of loops is high, race cases emerge.
    // loops wont be 2*loops, because at execution time the OS may interrupt the updating of the counter
    // variable, and jump to the other thread's worker make a dirty read, an update the counter too. this is because
    // updating the counter variable takes three steps, one loading the variable, updating it, then storing it, the context switcher
    // may halt a process midterm, and jump to the other thread (process).
    // This race problems are not limited to the OS itself, but also to the higher levelmulti-threaded applications.
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    printf("Final value :   %d\n", counter);
    return 0;
}
