#include <stdio.h>
#include <ucontext.h>

#include "printctx.h"

void func(void);

int  ctx = 0;
ucontext_t context, *cp = &context;

int main(void) {

  getcontext(cp);
  printf("User mode context obtained!\n");
  print_ucontext(cp);
  

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

