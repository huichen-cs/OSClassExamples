#include <stdio.h>
#include <ucontext.h>

void func(void);

int  ctx = 0;
ucontext_t context, *cp = &context;

int main(void) {

  getcontext(cp);
  printf("Hello, Context Switching!\n");
  

  if (!ctx) {
    printf("Saved context by calling getcontext. \n");
    func();
  }
  else {
    printf("Context restored by calling setcontext.\n");
  }

}

void func(void) {
  ctx ++;
  setcontext(cp);
}
