#define _GNU_SOURCE
#include <stdio.h>
#include <ucontext.h>

#include "printctx.h"

void print_ucontext(ucontext_t *uc) {
    printf("-------------------------------------------\n");
    printf("The (incomplete) user context:\n");
#ifdef __x86_64__
    printf("\tRegister RIP:  %llx\n", uc->uc_mcontext.gregs[REG_RIP]);
    printf("\tRegister RAX:  %llx\n", uc->uc_mcontext.gregs[REG_RAX]);
    printf("\tRegister RSP:  %llx\n", uc->uc_mcontext.gregs[REG_RSP]);
    printf("\tRegister RBP:  %llx\n", uc->uc_mcontext.gregs[REG_RBP]);
    printf("\tRegister RAX:  %llx\n", uc->uc_mcontext.gregs[REG_RAX]);
    printf("\tRegister RBX:  %llx\n", uc->uc_mcontext.gregs[REG_RBX]);
    printf("\tRegister RCX:  %llx\n", uc->uc_mcontext.gregs[REG_RCX]);
    printf("\tRegister RDX:  %llx\n", uc->uc_mcontext.gregs[REG_RDX]);
    printf("\tRegister RSI:  %llx\n", uc->uc_mcontext.gregs[REG_RSI]);
    printf("\tRegister RDI:  %llx\n", uc->uc_mcontext.gregs[REG_RDI]);
#else
    printf("\tRegister EIP:  %x\n", uc->uc_mcontext.gregs[REG_EIP]);
    printf("\tRegister CS:   %x\n", uc->uc_mcontext.gregs[REG_CS]);
    printf("\tRegister EAX:  %x\n", uc->uc_mcontext.gregs[REG_EAX]);
    printf("\tRegister EBX:  %x\n", uc->uc_mcontext.gregs[REG_EBX]);
    printf("\tRegister ECX:  %x\n", uc->uc_mcontext.gregs[REG_ECX]);
    printf("\tRegister EDX:  %x\n", uc->uc_mcontext.gregs[REG_EDX]);
    printf("\tRegister ESI:  %x\n", uc->uc_mcontext.gregs[REG_ESI]);
    printf("\tRegister EDI:  %x\n", uc->uc_mcontext.gregs[REG_EDI]);
    printf("\tRegister ESP:  %x\n", uc->uc_mcontext.gregs[REG_ESP]);
    printf("\tRegister EBP:  %x\n", uc->uc_mcontext.gregs[REG_EBP]);
#endif
    printf("-------------------------------------------\n");
}

