#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ucontext.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>

/* scheduler */
static const long NS_TO_FIRE_TIMER = 100000;
static const long STACK_SIZE = (1 << 14);

static void *timerhandler_stack;

static void timerhandler(int signal);
static void dispatcher();

/* two user threads */
static void make_hu_context();
static void hello_user();

static void make_hw_context();
static void hello_world();

/* threads and scheduler contexts */
static ucontext_t timerhandler_context, hu_context, hw_context, *active_context;



int main(int argc, char* argv[]) {

    /* prepare contexts for two user threads running two functions
     * concurrently */
    make_hu_context();
    make_hw_context();


    /* prepare timerhandler to run as a timer handler */
    timerhandler_stack = malloc(STACK_SIZE);

    struct sigaction sigact;

    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = 0;
    sigact.sa_handler = timerhandler;
    sigaction(SIGALRM, &sigact, NULL);

    struct itimerval itv;

    itv.it_interval.tv_sec = 0;
    itv.it_interval.tv_usec = NS_TO_FIRE_TIMER;
    itv.it_value = itv.it_interval;
    setitimer(ITIMER_REAL, &itv, NULL);


    /* activate the first context */
    active_context = &hu_context;
    setcontext(&hu_context);

    return 0;
}



static void hello_user() {
    for (int i=0; i<100; i++) {
        printf("[%03d]: Hello, User!\n", i);
        fflush(stdout);
        usleep(500000);
    }
}

static void hello_world() {
    for (int i=0; i<10; i++) {
        printf("[%03d]: Hello, World!\n", i);
        fflush(stdout);
        usleep(500000);
    }
}


static void make_hu_context() {
    getcontext(&hu_context);

    hu_context.uc_stack.ss_sp = malloc(STACK_SIZE);
    hu_context.uc_stack.ss_size = STACK_SIZE;
    hu_context.uc_stack.ss_flags = 0;

    makecontext(&hu_context, hello_user, 1);
}

static void make_hw_context() {
    getcontext(&hw_context);

    hw_context.uc_stack.ss_sp = malloc(STACK_SIZE);
    hw_context.uc_stack.ss_size = STACK_SIZE;
    hw_context.uc_stack.ss_flags = 0;

    makecontext(&hw_context, hello_world, 1);
}


/* thread scheduler consists of the timerhandler and the dispatcher */
static void timerhandler(int signal) {
    getcontext(&timerhandler_context);
    timerhandler_context.uc_stack.ss_sp = timerhandler_stack;
    timerhandler_context.uc_stack.ss_size = STACK_SIZE;
    timerhandler_context.uc_stack.ss_flags = 0;
    sigemptyset(&timerhandler_context.uc_sigmask);
    makecontext(&timerhandler_context, dispatcher, 1);

    swapcontext(active_context, &timerhandler_context);
    /* the active_context allows the thread to returns to previous active 
     * thread since when the active_conetxt is activated, it will resume
     * execution from right here */
}

static void dispatcher() {
    if (active_context == (&hu_context)) {
        active_context = &hw_context;
    } else if (active_context == (&hw_context)) {
        active_context = &hu_context;
    } else {
        printf("Programming Error: No such context!\n");
    }
    setcontext(active_context);
}
