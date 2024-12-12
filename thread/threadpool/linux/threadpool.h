#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__

#include <pthread.h>

typedef struct thread_pool_task_t {
  void *(*task_routine)(void *);
  void *args;
} thread_pool_task_t;

typedef struct thread_pool_t {
  int thread_num;
  int thread_count;
  pthread_t *tid;
  void *(*runner)(void *);
  thread_pool_task_t *task_list;
  int task_count;
  pthread_mutex_t mutex_task_list;
  pthread_cond_t cond_task_list;
  pthread_cond_t cond_can_exit;
  int can_exit;
} thread_pool_t;

thread_pool_t *thread_pool_create(int num_threads, int max_task_count);
void thread_pool_add_task(thread_pool_t *thread_pool,
                          void *(*task_routine)(void *), void *args);
// void thread_pool_join(thread_pool_t* thread_pool);
void thread_pool_wait(thread_pool_t *thread_pool);
void thread_pool_destroy(thread_pool_t *thread_pool);

#endif
