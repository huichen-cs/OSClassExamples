# User Mode Thread Scheduler

This program demonstrates the mechanism to schedule two threads running
in user mode using UNIX APIs:

- setcontext, getcontext, makecontext, and swapcontext
- signaling handling (using a sigaction function, with which we can examine
  the user context passed in as an argument of the sigaction function)

The program demonstrates we can use a timer to switch threads to CPU
preemptively. For the version that uses the signal handler function, see
[../um2tschedshc](../um2tschedshc).


In this example, note that algorithm the sigction function has the prototype
of 
```
void (*sigaction_func)(int signal_number, 
                       siginfo_t *siginfo, 
                       void *ucontext);
```
where `ucontext` points to a `ucontext_t` structure, and the structure
contains signal context information that was saved on the user-space stack by
the kernel. The user context pointed by this argument is commonly not used in
the function, and cannot be used to in context switching as it cannot be easily
copied and saved because the structure contains pointers. However, this 
argument can be used to examine the context, as this example program
demonstrates. 

