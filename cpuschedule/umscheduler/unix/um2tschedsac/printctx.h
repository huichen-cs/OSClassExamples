#ifndef PRINTCTX_H
#define PRINTCTX_H

#include <signal.h>

void print_ucontext(siginfo_t *si, ucontext_t *uc);

#endif
