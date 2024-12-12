#ifndef __PI_WORKER__
#define __PI_WORKER__

#include <stdint.h>

struct thread_info {
  pthread_t thread_id; /* ID returned by pthread_create() */
  int thread_num;      /* Application-defined thread # */
  int64_t maxiter;
  int seedx;
  int seedy;
  int64_t accepted;
};

void *piworker(void *thread_num);

#define handle_error_en(en, msg)                                               \
  do {                                                                         \
    errno = en;                                                                \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

#endif
