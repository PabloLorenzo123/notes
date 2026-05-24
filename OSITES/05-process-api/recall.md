# The Process API
let's remember that the OS offers a api library for programs to use, in the previous section processes were discussed and we defined them as the abstraction the OS use to manage multiple programs concurrently with the goal of virtualizing resources such as the cpu and memory.

In this note, we'll discuss the different functions UNIX expose to working with processes.

## Windows Sucks

### POSIX (Portable Operating System Interface, the x is for UNIX)
POSIX is an IEEE standard that defines how softeare should interact with the OS, with the goal of making software portable. By being more precise, it specifies what systems calls and cli commands should the operating systems have. In this standard is defined the process api: fork(), wait(), exec(), kill(), etc. Most OS follow this standard such as Unix, Linux and MAC except for Windows.

This causes the need to write different code for Windows and UNIX like system as they have different system calls.

This affect C source code, that executes system call directly. So in windows we can't program C code with the methods fork(), wait(), exec().

[VIDEO NOTE](https://youtu.be/YaFJEtGbQT8?si=F_mxAqBzHhmhpY5n)

### How to deal with it.
We can spin up a linux vm, or use the WSL (Windows Subsystem for Linux). How i handled this limitation is by installing the WSL extension in vs code, and installing WSL on my windows computer with the Ubuntu image and installing the basic-tools gcc, etc.

Then in vs code i do control + p > wsl, and open the folder, open the wsl terminal and ready to work.

## FORK()
Fork is a **system call** that creates a new child proccess, the copied child process its a copy of the parent process, including its registers current state at the moment the fork() was called in. Meaning the PC of the child process will begin pointing to fork().

fork() returns 1 for the parent process, and returns 0 for the child process. -1 in case of failure.

ex:
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("hello world (pid: %i)\n", getpid());
    int rc = fork(); // The kernel will create a copy of the running processes, including copying the pc register.
    // this fork() will return 1 or -1 for the parent process, and 0 for the child process.
    if (rc == -1){
        printf("There was an error trying to create a child process.\n");
        exit(1);
    }
    else if (rc == 0){
        printf("hello, i am child (pid: %i)\n", getpid());
    }
    else {
        printf("hello, i am parent of %i (pid:%i)\n", rc, getpid());
    }
    return 0;
}
```

## WAIT()
the parent process will not continue execution until child process is done, ex:

```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    printf("Hello i'm (pid: %i)\n", getpid());

    int rc = fork(); // a child process is created.
    if (rc == -1){
        printf("There was an error while trying to create a child process.\n");
        exit(1);
    }
    else if (rc == 0){
        // This work needs to be completed before parent continues execution.
        for (int i = 0; i < 100; i++){
            printf("child %i, ", i);
        }
        printf("\n");
    }
    else {
        printf("Hi i'm parent the scheduler called me, but i won't continue until child is done.\n");
        wait(NULL);

        for (int i = 0; i < 100; i++){
            printf("parent %i, ", i);
        }
        printf("\n");
    }

    return 0;
}

```

## EXEC()
exec() will override the current process code and restart the pc register, call stack and heap. But the file descriptors will remain unchanged.

ex:

```
void execExample(int argc, char* argv[]) {
    if (argc != 3){
        printf("usage: ./practice file_to_read > output.txt\n");
        exit(1);
    }

    char* read_from = argv[1];
    char* save_in = argv[2];
    int child = fork();

    if (child == -1){
        printf("There was an error while trying to create a child process.\n");
        exit(1);
    }
    else if (child == 0){
        // we can cook something before calling exec.
        int of = open(save_in, O_CREAT); // CREATE FILE IF MISSING.
        close(of); // open() returns the file descriptor number.

        char* program = "wc";
        char* execArgs[] = {program, read_from, NULL};

        // trick: we want wc to output its result into a file, instead of the terminal.
        // file descriptors come into play here, these are tables that match a number to a file.
        // unix philosophy is that everything is a file, the terminal, a file, the disk..
        // wc what it does is that it writes() to whatever the file descriptor entry 1 points to.
        
        close(1); // ENTRY FOR KEY 1 IN DESCRIPTOR TABLE IS NOW FREE.
        open(save_in, O_WRONLY); // ENTRY KEY 1 NOW HAS THE FILE SET INTO THERE.

        // replace this process code with the wc.
        execvp(execArgs[0], execArgs);
    }
    else {
        wait(NULL);
        printf("wc program is done\n.");
    }
}
```

## Pipes
consist of this | , the output from the previous process is the input for the new process.

# lampson's Law
As lampson states in his well-regarded "Hitns for Computer Systems Design", **Get it right**. Neither abstraction nor simplicity is a substitue for getting it right. Sometimes, you just have todo the right thing, and when you do, it is way better than the alternatives. There are lots of ways to design APIs for process creation; howerver, the combination of fork() and exec() are simple and inmensely powerful. Here, the UNIX designers simply got it right. And because Lampson so often "got it right", we name the law in his honor.
