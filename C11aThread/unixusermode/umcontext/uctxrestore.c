#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

int main(int argc, const char *argv[]){
    ucontext_t curr;

    getcontext(&curr);
    puts("After getcontext: Hello, World!");
    sleep(1);
    setcontext(&curr);
    puts("After setcontext: Hello, World!");
    return 0;
}
