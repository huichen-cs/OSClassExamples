#include <stdlib.h>
#include <stdio.h>
#include <ucontext.h>

#define STACK_SIZE (1 << 14)

static void hello_user();
static void make_hu_context();

ucontext_t hu_context;


int main(int argc, char *argv[]) {
    make_hu_context();
    setcontext(&hu_context);
    return 0;
}

static void hello_user() {
    printf("Hello, User!\n");
}

static void make_hu_context() {
    getcontext(&hu_context);

    hu_context.uc_stack.ss_sp = malloc(STACK_SIZE);
    hu_context.uc_stack.ss_size = STACK_SIZE;

    makecontext(&hu_context, hello_user, 0);
}

