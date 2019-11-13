#define _GNU_SOURCE /* register constants */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ucontext.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>

#include "printctx.h"

/* stack size for scheduler and user threads */
static const long STACK_SIZE = (1 << 14);

/* scheduler */
static const long NS_TO_FIRE_TIMER = 100000;
static void *timerhandler_stack;
static void run_scheduler();
static void make_timerhandler_context();
static void timeraction(int signum, siginfo_t *siginfo, void *ucontext);
static void dispatcher();

/* two user threads, the "hello user" and the "hello world" threads */
static void *hu_stack;
static void make_hu_context();
static void hello_user();
static void hu_stub();
static int  hu_exited;

static void *hw_stack;
static void make_hw_context();
static void hello_world();
static void hw_stub();
static int  hw_exited;

/* threads and scheduler contexts */
static ucontext_t timerhandler_context, hu_context, hw_context, *active_context;

static void cleanup() {
    free(hu_stack);
    free(hw_stack);
    free(timerhandler_stack);
    printf("\tNo more threads to schedule. Exiting the program ...\n");
}

int main(int argc, char* argv[]) {
    atexit(cleanup);

    /* make timerhandler context */
    make_timerhandler_context();
    printf("\tInitialized timer interrupt handler context.\n");
    print_ucontext(NULL, &timerhandler_context);

    /* prepare contexts for two user threads running two functions
     * concurrently */
    make_hu_context();
    hu_exited = 0;
    printf("\tInitialized the 'hello user' thread context.\n");
    print_ucontext(NULL, &hu_context);

    make_hw_context();
    hw_exited = 0;
    printf("\tInitialized the 'hello world' thread context.\n");
    print_ucontext(NULL, &hw_context);


    /* prepare timerhandler to run as a timer handler */
    struct sigaction sigact;

    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = SA_RESTART | SA_SIGINFO;
    sigact.sa_sigaction = timeraction;
    sigaction(SIGALRM, &sigact, NULL);

    struct itimerval itv;

    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = NS_TO_FIRE_TIMER;
    itv.it_value = itv.it_interval;
    setitimer(ITIMER_REAL, &itv, NULL);
    printf("\tSet up timer that is to fire every %ld nanoseconds\n", 
            NS_TO_FIRE_TIMER);


    /* activate the first context */
    printf("\tNow starting the scheduler.\n");
    run_scheduler();

    return 0;
}

static void hu_stub() {
    hello_user();
    hu_exited = 1;
}


static void hello_user() {
    for (int i=0; i<4; i++) {
        printf("[%03d]: Hello, User!\n", i);
        fflush(stdout);
        usleep(500000);
    }
}

static void hw_stub() {
    hello_world();
    hw_exited = 1;
}

static void hello_world() {
    for (int i=0; i<2; i++) {
        printf("[%03d]: Hello, World!\n", i);
        fflush(stdout);
        usleep(500000);
    }
}

static void run_scheduler() {
    /* select a thread, i.e., in this case, the hell user thread */
    active_context = &hu_context;
    /* run the thread */
    setcontext(&hu_context);
}

static void make_timerhandler_context() {
    getcontext(&timerhandler_context);
    timerhandler_stack = malloc(STACK_SIZE);
    timerhandler_context.uc_stack.ss_sp = timerhandler_stack;
    timerhandler_context.uc_stack.ss_size = STACK_SIZE;
    timerhandler_context.uc_stack.ss_flags = 0;
    sigemptyset(&timerhandler_context.uc_sigmask);
    makecontext(&timerhandler_context, dispatcher, 0);
}

static void make_hu_context() {
    getcontext(&hu_context);

    hu_stack = malloc(STACK_SIZE);
    hu_context.uc_stack.ss_sp = hu_stack;
    hu_context.uc_stack.ss_size = STACK_SIZE;
    hu_context.uc_stack.ss_flags = 0;
    hu_context.uc_link = &timerhandler_context;

    makecontext(&hu_context, hu_stub, 0);
}

static void make_hw_context() {
    getcontext(&hw_context);

    hw_stack = malloc(STACK_SIZE);
    hw_context.uc_stack.ss_sp = hw_stack;
    hw_context.uc_stack.ss_size = STACK_SIZE;
    hw_context.uc_stack.ss_flags = 0;
    hw_context.uc_link = &timerhandler_context;

    makecontext(&hw_context, hw_stub, 0);
}


/* thread scheduler consists of the timerhandler and the dispatcher */
static void timeraction(int signum, siginfo_t *siginfo, void *ucontext) {
    printf("\tEntering timer interrupt handler: time slice expired. "
           "Invoke scheduler ...\n");
    print_ucontext(siginfo, (ucontext_t *)ucontext);
    swapcontext(active_context, &timerhandler_context);
    /* the active_context allows the thread to returns to previous active 
     * thread since when the active_conetxt is activated, it will resume
     * execution from right here */
    printf("\tExiting timer interrupt handler ...\n");
}

static void dispatcher() {
    if (hu_exited && hw_exited) {
        printf("\tDispatcher: both hu and hw threads exited\n");
        return;
    }
    if (active_context == (&hu_context) && !hw_exited) {
        active_context = &hw_context;
        printf("\tDispatcher: selected hw thread to run\n");
    } else if (active_context == (&hw_context) && !hu_exited) {
        active_context = &hu_context;
        printf("\tDispatcher: selected hu thread to run\n");
    } 
    printf("\tDispatcher: dispatch the thread to CPU\n");
    print_ucontext(NULL, active_context);
    setcontext(active_context);
}

