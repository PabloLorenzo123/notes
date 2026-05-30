# CPU Virtualization
CPU virtualization is a tehnique used with the goal of sharing the cpu between processes without these having the need to bother with the fact that the cpu is a shared resource, this way they can behave as if they're the only process in the OS, this result in easier development experience, because a programmer needs only to care about the program currently being written.

To achieve this goal, which is a huge part of our OS design. We used mechanisms and policies, because as in many cases with the kernel & os, software alone can't achieve the goal, so hardware mechanisms and software policies need to be implemented and work hand by hand to achieve it.

## The Process Abstraction

The program only lives inside a process, a process encapsulates and controls the program's code and state. Before running a program, which code is usually saved in a persistent storage such as a hard drive, ssd or flash, the OS first needs to read this code and load it into memory along with its static variables. Once it's in memory, and the process is in a running state, then the program starts. A program to function needs, code (of course), static variables (if any), a stack (stack frames are pushed into here, everytme a function is called a stack frame is appended), a heap which is the dynamic memory slot in where we save dynamically allocated variables such as objects, a progrma counter, registers, file descriptors, a pid (process identifier) and a memory address spase.

## PCB - Proccess List - Process Control Block

Because, an OS can run multiple programs at the same time, each program/process need to have its own state persisted somewhere, because as we may already know the OS achieves the ilussion of "paralellism - multiple programs at the same time", by concurrently running each process. If we switch between processes and don't persist the information each process need which we discussed in the previous paragraph, then each time we get back to a process it will have an erroneus state. The place were we persist each process context is in the PCB (Process Control Block). When the scheduler gets back to a process, it first needs to save the state of the current process, then load the context of the new process and then start running it.

### States
A process can hve multiple states, but the most basic are:
- RUNNING: the instructions of the process are currently being executed.
- READY: the instructions are not running, but the process can be started anytime.
- BLOCKED / WAITING: The process is waiting for another process to complete, before resuming execution, such as AN I/O operation.
- Zombie: When a parent process, creates a child process by fork(), but doesn't wait() for the child process return value, then the child process is said to be in a zombie state.
- Orphan: when a parent process, creates a child process by fork(), but the parent process exists earlier than the child, then the child is in a orphan state.
- Done.

Only a process can be active at a time. The scheduler executes the instructions of the active process until:
1 - The scheduler decides it's enough, maybe its maximum time exceded or a trap was triggered, or a policy needs to be applied.
2 - The process enters a blocking state.

