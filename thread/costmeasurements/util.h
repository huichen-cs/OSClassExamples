#ifndef __NSTIME_H__
#define __NSTIME_H__

#include <stdint.h>

uint64_t get_ns_time();
void errorExit(char *msg);
void allocateAndUseBuf(int mb);

#endif
