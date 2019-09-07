# User Mode Thread Scheduler

This program demonstrates the mechanism to schedule two threads running
in user mode using UNIX APIs:

- setcontext, getcontext, makecontext, and swapcontext
- signaling handling (using a signal handler function)

The program demonstrates we can use a timer to switch threads to CPU
preemptively. This is a complete version of the example in the directory
[../um2tschedshs](../um2tschedshs).

