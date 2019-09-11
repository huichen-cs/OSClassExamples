#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>

#include "printctx.h"

#define STACK_SIZE (1 << 14)

static void hello_user();
static void make_hu_context();

ucontext_t hu_context;


int main(int argc, char *argv[]) {
#ifdef __x86_64__
    printf("hello_user is at %lp\n", &hello_user);
#else
    printf("hello_user is at %p\n", &hello_user);
#endif
    make_hu_context();
    setcontext(&hu_context);
    return 0;
}

static void hello_user() {
    printf("From hello_user: Hello, User!\n");
}

static void make_hu_context() {
    getcontext(&hu_context);
    printf("Newly obtained hu_context:\n");
    print_ucontext(&hu_context);

    hu_context.uc_stack.ss_sp = malloc(STACK_SIZE);
    hu_context.uc_stack.ss_size = STACK_SIZE;

    makecontext(&hu_context, hello_user, 0);
    printf("hu_context made via makecontext:\n");
    print_ucontext(&hu_context);
}

