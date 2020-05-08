/*
 * See
 *  https://www.felixcloutier.com/x86/cpuid#tbl-3-12
 *  for interpretation of returned byte values 
 *
 *  and the discussion at
 *
 *  https://stackoverflow.com/questions/58128776/understanding-tlb-from-cpuid-results-on-intel
 *
 */
#include <cpuid.h>  // GCC-provided
#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t eax, ebx, ecx, edx;
    if (__get_cpuid(0x00000002, &eax, &ebx, &ecx, &edx)) { 
        printf(
            "Look up byte values from https://www.felixcloutier.com/x86/cpuid#tbl-3-12\n"
            "\teax: 0x%08x\n"
            "\tebx: 0x%08x\n"
            "\tecx: 0x%08x\n"
            "\tedx: 0x%08x\n", 
            eax, ebx, ecx, edx);
        return 0;
    } else {
        return 2;
    }
}
