# Restricted Limited Execution
We're still in the virtualization part, where we've already disccused the ```process`` abstraction, and the POSIX api offer to us programmers system cals such as: fork(), exec(), wait(), pipe().

But now we've faced with another challenge in designing our operating system, how can we limit what each process can do? and how can we ensure the OS keeps control of the machine? because as you know, the CPU can only execute a process at a time, and while the process has its turn, the OS is not in control. How does the software and hardware cooperate to solve these callenges?

## Execution Modes
The CPU has a bit, which differentiate between user and kernel mode, when kernel mode bit is on a set of instructions are now available to the cpu. User programs should run in user mode, and the OS in kernel. That's how we limit what an user process can do. But you may wonder, how can we allow an user process to execute important instructions such as I/O operations.

Let's first understand what an interrupt is.

## Interrupts.
A system interrupt, is a signal sent to the cpu, that makes the PC register jump to a predefined location where the code to handle the interrupt lives. Interrupts can be triggered by I/O such as pressing a key in the keyboard, or by a system call.

### System Calls
System calls are procedure and wrappers of system traps. The cpu has a instruction, which triggers a trap. When a user program calls a system call such as open(), this wrapper function do interesting things, first it validates the parameters and save them in the appropiate registers the trap handler will read from when it gets its turn. Finally the trap is called, an interrupt struction is called, the cpu jumps the pc register, and the OS takes over, the OS will then run in ```the user's program behalf``` and execute the restricted instructions, once it's done if will return with a ```return-from-trap``` instruction, in where the user program will continue on running.

But it's not this easy, let's go more in detail into what happens when we make a system call. First, before executing the trap, the currently running program registers, code, state, flags are saved in a PCB table this is important because we need to know the state of the process when we eventually get back to it.

Another thing is, that during the trap, the OS may decide to stop the previously running process, and continue on with another process instead, this is called ```context switch```, if it does this, then it needs to save the ```kernel state``` of the currently running process, so that whenever we go back to this program we continue on with the trap handler code in the correct state.

Note: a system call is called by a number, for instance trap(1) may proceed to read from disk. If an user programs tries to execute a restricted instrution, and interrupt is triggered and it's likely that the OS kill the proccess.

## The trap table
When the machine starts, the cpu executes a ```bootloader``` this bootloader has some code, that sets up the trap table for the cpu, this way no user program can put their code in it.

# How to prevent a Process from locking the CPU
The CPU can only execute an instruction at a time, a program at a time. Our next challenge is, how can we prevent a process for taking over the compute of the machine?

## COOPERATIVE APPROACH
One way is the cooperative approach, we as OS developers just trust that the user's application will eventually call a system call (in a system call we can decide to switch process if we like - hence why it's called a trap!), or that the user's program themselve will willingly pass control back to the OS. This approach is uncommon, for reasons you may have already guessed, what an evil world we live in.

## NON-COOPERATIVE APPROACH
We can program the CPU to start a timer, each time the timer runs up it will trigger an interrupt and pass control back to the OS, which then will decide how to proceed. This way is impossible for a process to kidnap the CPU.

# RESOURCES:
[video](https://www.youtube.com/watch?v=H4SDPLiUnv4&t=310s) This video is exactly the video form of this chapter.
