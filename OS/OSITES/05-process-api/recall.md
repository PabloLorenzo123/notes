# The Process API
let's remember that the OS offers a api library for programs to use, in the previous section processes were discussed and we defined them as the abstraction the OS use to manage multiple programs concurrently with the goal of virtualizing resources such as the cpu and memory.

In this note, we'll discuss the different functions UNIX expose to working with processes.

## Windows Sucks

### POSIX (Portable Operating System Interface, the x is for UNIX)
POSIX is an IEEE standard that defines how software should interact with the OS, with the goal of making software portable. By being more precise, it specifies what systems calls and cli commands should the operating systems have. In this standard is defined the process api: fork(), wait(), exec(), kill(), etc. Most OS follow this standard such as Unix, Linux and MAC except for Windows.

This causes the need to write different code for Windows and UNIX like system as they have different system calls.

This affect C source code, that executes system call directly. So in windows we can't program C code with the methods fork(), wait(), exec().

[VIDEO NOTE](https://youtu.be/YaFJEtGbQT8?si=F_mxAqBzHhmhpY5n)

### How to deal with it.
We can spin up a linux vm, or use the WSL (Windows Subsystem for Linux). How i handled this limitation is by installing the WSL extension in vs code, and installing WSL on my windows computer with the Ubuntu image and finally installing the basic-tools gcc, etc.

Then in vs code i do control + p > wsl, and open the folder, open the wsl terminal and ready to work.

## FORK()
Fork is a **system call** that creates a new child proccess, the copied child process its a copy of the parent process, including its registers current state at the moment the fork() was called in. Meaning the PC of the child process will begin pointing to fork().

fork() returns the pid of the child proccess (>= 1) for the parent process, and returns 0 for the child process. -1 in case of failure.

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
consist of this | , the output from the previous process is the input for the new process. The kernel offers the pipe() system call, which allows for IPC (inter process comunication), the pipe() takes as an argument an array of length 2. in where index 0 will be the buffer descriptor to write to the pipe, and 1 the one the descriptor to read from. this frees up from using a file to share messages between processes.

ex:
```
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

// To demonstrate pipes, let's create a program what from the current directory files
// filter files with a certain name, using the built-in unix functions.
// using ls and wc which are standard POSIX utilities that POSIX compliant operating systems are expected to provide.
// ls and wc are part of the POSIX userland utilities, not kernel featurres.
// POSIX (Portable Operating System Interface) and the X -> UNIX. POSIX defines both userland utilities (cat, ls, wc) and System intercaes (open, read, write, close, fork).
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("usage: ./pipes [folder_file_name_to_look_for].\n");
        exit(1);
    }
    char *word = argv[1];

    int fd[2];
    // pipe will add at index 0, a read-end, and at index 1 a write-end. these numerical values will represent
    // file descriptors.
    pipe(fd);

    // now i create a copy of this process, (pc, stack, static code, and most importantingly file descriptors).
    pid_t lschild = fork();

    if (lschild == 0) // child goes here.
    {
        // still unclear why we need to close this, but suppose now that its because we won't use this.
        close(fd[0]);
        // close(STDOUT_FILENO); // let's close the output file descriptor, which at this point is the terminal.
        // fopen(fd[1]);         // now the descriptor for this will be the 1 (output), ls will print to this fd[1].
        dup2(fd[1], STDOUT_FILENO); // this will put fd[1] in the descriptor of STDOUT_FILE.

        char *args[] = {"ls", NULL};
        execvp("ls", args);

        // if exec is succesful, remember the the process code is all overwritten, so these lines would never execute.
        perror("execvp ls");
        exit(1);
    }

    // parent will wait for ls to be done.
    waitpid(lschild, NULL, 0);

    // now let's run wc.
    pid_t wcchild = fork();

    if (wcchild == 0)
    {                 // it's the child process running here.
        close(fd[1]); // this process won't write. it's important to close it because read(fd[0]) will only return EOF, when all fd[1] are closed.
        // close(STDIN_FILEIN); // close reading descriptor.
        // open(fd[0]);         // what ls buffered up, can now be read here.
        dup2(fd[0], STDIN_FILENO);

        char *params[] = {word, NULL};
        execvp("wc", params);

        // if exec is succesful, remember the the process code is all overwritten, so these lines would never execute.
        perror("wc");
        exit(1);
    }

    
    close(fd[0]);
    close(fd[1]); // if we omit this, this program will run forever, because wc the reader will never get the EOF.

    waitpid(wcchild, NULL, 0);

    return 0;
}

```

NOTE: Close every pipe end that a process does not need, because open write ends prevent readers from seeing EOF.

## Signals
A signal is a notification to a process, should as 'stop' with ctrl-c the program can catch a **SIGINT** signal, and maybe exit gracefully.

Another signal is **SIGTERM**: Please shut down nicely.
**SIGKILL**: Die inmediately.

ex:
```
#include <stdio.h>
#include <signa.h>
#include <unistd.h>
#include <stdbool.h>

void handle_sigint(int signal_number){
    printf("Hello gooodbye.\n");
}

int main(void) {
    signal(SIGINT, handlesigint);

    while (1){
        printf("Working...\n");
        sleep(1);
    }

    return 0;
}
```

### CONNECTION: WHY DOCKER PREFERS EXEC MODE OVER SHELL MODE WHEN EXECUTING COMMANDS.

When executing a command in a Dockerfile - the file that specifies how a container should be built, there are two ways to write the command (CMD). One approach is, the shell mode, is simply writing the command, ex:

```
FROM node

COPY . .

CMD npm start 
```

docker actually does
```
/bin/sh -c "npm start"
```

This means the shell process ```sh``` becomes PID 1 inside the container, while the actual application process ```npm``` becomes a child process. This can create issues with signal handling.

this approach has the following issue, when the container is running, let's say in an attached mode, when you press CTRL + C (which triggers a SIGINT) signal, it's likely that the process receiving this signal won't be npm, but rather the shell proccess which called npm, meaning the parent process of npm. Additionally, PID 1 in Linux has special responsibilities and signal-handling behavior. If the shell is PID 1 instead of the application itself, graceful shutdowns may fail, potentially leaving child processes running temporarily or forcing Docker to kill the container abruptly with SIGKILL after a timeout.

This is why docker recommends using the exec form, which ensures that the npm process has the PID 1 and will receive te signals correctly.

Well npm is not a good example, because this is a wrapper process which called node. this is why developer prefer using node in the cmd, instead of a npm script defined in the package.json.

ex:

```
FROM node

COPY . .

CMD [ "npm", "start" ]
```


## Users
Users are used to identify what processes can use other processes, and what they can do with files. For instance as you saw earlier, we made a program which can call ls and wc, and even read some files, the kernel allows this because the user that triggered the program have the correct priviliges to execute these other programs. But image a malicious script, which try to delete the entire computer, the kernel needs to protect against that, for this the concept of ``users`` is borned, if this maliccious program run as low privilige user then it may not cause harm, but if you `run it as administrator` it may cause harm.

In UNIX, when we need to do high privilige things, we use the `sudo` user, this user can do anything.

chatgpt:
In UNIX/POSIX systems, users are represented internally by numeric user IDs, usually called UIDs. Every process runs with a user identity, and the kernel uses that identity to decide what the process is allowed to do.

For example, when a process tries to read a file, write to a file, execute a program, or signal another process, the kernel checks the process's user and group IDs against the permissions of the target resource.

If I write a program that executes ls and wc, the kernel allows it only if the process has permission to execute those programs and access the files involved. The program itself does not have unlimited power; it can only do what its user identity is allowed to do.

This is important for security. Imagine a malicious script that tries to delete system files. If that script runs as a normal low-privilege user, the kernel should prevent it from deleting files owned by the system or by other users. But if the same script runs with administrator-level privileges, it may be able to cause much more damage.

In UNIX-like systems, the most powerful user is called root. The root user usually has UID 0 and can bypass many normal permission checks.

The command sudo is not a user. It is a program that allows authorized users to run commands as another user, commonly as root. So when people say “run it with sudo,” they usually mean “run this command with root privileges.”

# lampson's Law
As lampson states in his well-regarded "Hitns for Computer Systems Design", **Get it right**. Neither abstraction nor simplicity is a substitue for getting it right. Sometimes, you just have todo the right thing, and when you do, it is way better than the alternatives. There are lots of ways to design APIs for process creation; howerver, the combination of fork() and exec() are simple and inmensely powerful. Here, the UNIX designers simply got it right. And because Lampson so often "got it right", we name the law in his honor.
