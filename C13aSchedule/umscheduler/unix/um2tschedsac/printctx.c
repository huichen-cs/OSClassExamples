#define _GNU_SOURCE
#include <stdio.h>
#include <ucontext.h>

#include "printctx.h"

void print_ucontext(siginfo_t *si, ucontext_t *uc) {
    /* printf("\t-------------------------------------------\n"); */
    printf("\tThe (incomplete) user context:\n");
    if (NULL != si) {
        printf("\t\tSignal number: %d\n", si->si_signo);
    }
#ifdef __x86_64__
    printf("\t\tRegister RIP:  %llx\n", uc->uc_mcontext.gregs[REG_RIP]);
    printf("\t\tRegister RAX:  %llx\n", uc->uc_mcontext.gregs[REG_RAX]);
    printf("\t\tRegister RSP:  %llx\n", uc->uc_mcontext.gregs[REG_RSP]);
    printf("\t\tRegister RBP:  %llx\n", uc->uc_mcontext.gregs[REG_RBP]);
    printf("\t\tRegister RAX:  %llx\n", uc->uc_mcontext.gregs[REG_RAX]);
    printf("\t\tRegister RBX:  %llx\n", uc->uc_mcontext.gregs[REG_RBX]);
    printf("\t\tRegister RCX:  %llx\n", uc->uc_mcontext.gregs[REG_RCX]);
    printf("\t\tRegister RDX:  %llx\n", uc->uc_mcontext.gregs[REG_RDX]);
    printf("\t\tRegister RSI:  %llx\n", uc->uc_mcontext.gregs[REG_RSI]);
    printf("\t\tRegister RDI:  %llx\n", uc->uc_mcontext.gregs[REG_RDI]);
#else
    printf("\t\tRegister EIP:  %x\n", uc->uc_mcontext.gregs[REG_EIP]);
    printf("\t\tRegister CS:   %x\n", uc->uc_mcontext.gregs[REG_CS]);
    printf("\t\tRegister EAX:  %x\n", uc->uc_mcontext.gregs[REG_EAX]);
    printf("\t\tRegister EBX:  %x\n", uc->uc_mcontext.gregs[REG_EBX]);
    printf("\t\tRegister ECX:  %x\n", uc->uc_mcontext.gregs[REG_ECX]);
    printf("\t\tRegister EDX:  %x\n", uc->uc_mcontext.gregs[REG_EDX]);
    printf("\t\tRegister ESI:  %x\n", uc->uc_mcontext.gregs[REG_ESI]);
    printf("\t\tRegister EDI:  %x\n", uc->uc_mcontext.gregs[REG_EDI]);
    printf("\t\tRegister ESP:  %x\n", uc->uc_mcontext.gregs[REG_ESP]);
    printf("\t\tRegister EBP:  %x\n", uc->uc_mcontext.gregs[REG_EBP]);
#endif
    printf("\t-------------------------------------------\n");
}

