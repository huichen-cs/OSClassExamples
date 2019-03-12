# User Mode Thread Scheduler

These program demonstrates the mechanism to schedule threads running
in user mode using UNIX APIs:

- setcontext, getcontext, makecontext, and swapcontext
- signaling handling (using a sigaction function, with which we can examine
  the user context passed in as an argument of the sigaction function)


- signal. A few examples about signals.
- um2tschedsac. 2-thread scheduler using sigaction
- um2tschedshc. 2-thread scheduler using signal handler 
- um2tschedshs. An incomplete but simpler 2-thread scheduler to demonstrate
  the mechanism to do thread scheduling in user mode
