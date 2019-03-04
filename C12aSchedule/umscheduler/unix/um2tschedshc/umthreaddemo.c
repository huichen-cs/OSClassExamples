#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ucontext.h>
#include <sys/time.h>
#include <sys/types.h>
#include <signal.h>

/* stack size for scheduler and user threads */
static const long STACK_SIZE = (1 << 14);

/* scheduler */
static const long NS_TO_FIRE_TIMER = 100000;
static void *timerhandler_stack;
static void run_scheduler();
static void make_timerhandler_context();
static void timerhandler(int signal);
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
    printf("Exiting the program ...\n");
}

int main(int argc, char* argv[]) {
    atexit(cleanup);

    /* make timerhandler context */
    make_timerhandler_context();

    /* prepare contexts for two user threads running two functions
     * concurrently */
    make_hu_context();
    hu_exited = 0;

    make_hw_context();
    hw_exited = 0;


    /* prepare timerhandler to run as a timer handler */
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
    run_scheduler();

    return 0;
}

static void hu_stub() {
    hello_user();
    hu_exited = 1;
    // timerhandler(SIGALRM);
}


static void hello_user() {
    for (int i=0; i<100; i++) {
        printf("[%03d]: Hello, User!\n", i);
        fflush(stdout);
        usleep(500000);
    }
}

static void hw_stub() {
    hello_world();
    hw_exited = 1;
    // timerhandler(SIGALRM);
}

static void hello_world() {
    for (int i=0; i<10; i++) {
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
static void timerhandler(int signal) {
    swapcontext(active_context, &timerhandler_context);
    /* the active_context allows the thread to returns to previous active 
     * thread since when the active_conetxt is activated, it will resume
     * execution from right here */
}

static void dispatcher() {
    if (active_context == (&hu_context) && !hw_exited) {
        active_context = &hw_context;
    } else if (active_context == (&hw_context) && !hu_exited) {
        active_context = &hu_context;
    } 
    setcontext(active_context);
}
