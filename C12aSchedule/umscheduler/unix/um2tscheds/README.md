# User Model Thread Scheduler

This program demonstrates the mechanism to schedule two threads running
in user mode using UNIX APIs:

- setcontext, getcontext, makecontext, and swapcontext
- signaling handling

The program demonstrates we can use a timer to switch threads to CPU
preemptively; however, the program isn't complete because one threads
may not run to completion if one thread exits. This is done intentionally
to amplify the mechanism to do the preemptive scheduling.

