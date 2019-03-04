#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

int main(int argc, const char *argv[]){
    ucontext_t curr;

    getcontext(&curr);
    printf("%ld\n",sizeof(curr));
    puts("Hello world");
    sleep(1);
    setcontext(&curr);
    return 0;
}
