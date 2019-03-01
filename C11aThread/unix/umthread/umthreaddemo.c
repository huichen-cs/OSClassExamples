#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ucontext.h>

#define STACK_SIZE (1 << 14)

static void make_hu_context();
static void hello_user();

static void make_hw_context();
static void hello_world();
static ucontext_t m_context, hu_context, hw_context, main_context;
static int hu_exited = 0, hw_exited = 0;


int main(int argc, char* argv[]) {

    make_hu_context();
    make_hw_context();

    
    /* A simple non-preemptive round robin scheduler: 
     * Below is the main dispatch loop */
    while (1) {
        if (hu_exited) {
            printf("The hello user thread has exited.\n");
        }
        if (hw_exited) {
            printf("The hello world thread has exited.\n");
        }

        /* no more threds to schedule */
        if (hw_exited && hu_exited) {
            break;
        }

        /* dispatch the hello user thread to CPU */
        if (!hu_exited) {
            swapcontext(&main_context, &hu_context);
        }

        /* dispatch the hellow world thread to CPU */
        if (!hw_exited) {
            swapcontext(&main_context, &hw_context);
        }
    }

    return 0;
}

static void hello_user() {
    for (int i=0; i<20; i++) {
        printf("[%03d]: Hello, User!\n", i);
        fflush(stdout);
        usleep(50000);

        /* yeild to the scheduler thread */
        if (!hw_exited) {
            swapcontext(&hu_context, &main_context);
        }
    }

    /* yeild to the scheduler thread */
    printf("hu exiting ...\n");
    hu_exited = 1;
    swapcontext(&hu_context, &main_context);
}

static void hello_world() {
    for (int i=0; i<10; i++) {
        printf("[%03d]: Hello, World!\n", i);
        fflush(stdout);
        usleep(50000);

        /* yeild to the scheduler thread */
        if (!hw_exited) {
            swapcontext(&hw_context, &main_context);
        }
    }

    /* yeild to the scheduler thread */
    printf("hw exiting ...\n");
    hw_exited = 1;
    swapcontext(&hw_context, &main_context);
}


static void make_hu_context() {
    getcontext(&hu_context);

    hu_context.uc_stack.ss_sp = malloc(STACK_SIZE);
    hu_context.uc_stack.ss_size = STACK_SIZE;

    makecontext(&hu_context, hello_user, 0);
}

static void make_hw_context() {
    getcontext(&hw_context);

    hw_context.uc_stack.ss_sp = malloc(STACK_SIZE);
    hw_context.uc_stack.ss_size = STACK_SIZE;

    makecontext(&hw_context, hello_world, 0);
}

