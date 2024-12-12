/*
 * This is from
 * https://en.wikipedia.org/wiki/CPUID#EAX=80000006h:_Extended_L2_Cache_Features
 */
#include <cpuid.h>  // GCC-provided
#include <stdint.h>
#include <stdio.h>

int main(void) {
  uint32_t eax, ebx, ecx, edx;
  if (__get_cpuid(0x80000006, &eax, &ebx, &ecx, &edx)) {
    printf("Extended L2 Cache Features:\n"
           "\tLine size: %d B, Assoc. Type: %d; Cache Size: %d KB.\n",
           ecx & 0xff, (ecx >> 12) & 0x07, (ecx >> 16) & 0xffff);
    return 0;
  } else {
    fprintf(stderr, "CPU does not support 0x80000006");
    return 2;
  }
}
