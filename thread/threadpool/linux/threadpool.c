#include <stdlib.h>
#include <stdio.h>
#include <threadpool.h>


static void* thread_pool_runner(void* args) {
    thread_pool_t *tp = (thread_pool_t *)args;
    while (1) {
        thread_pool_task_t task;
        int found = 0;

        pthread_mutex_lock(&tp->mutex_task_list);
        while (tp->task_count == 0 && !tp->can_exit) {
            pthread_cond_wait(&tp->cond_task_list, &tp->mutex_task_list);
        }

        if (tp->can_exit) {
            // printf("terminating the thread\n");
            break;
        }

        task = tp->task_list[0];
        int i;
        for (i=0; i<tp->task_count-1; i++) {
            tp->task_list[i] = tp->task_list[i+1];
        }
        tp->task_count--;

        pthread_mutex_unlock(&tp->mutex_task_list);

        task.task_routine(task.args);

        pthread_mutex_lock(&tp->mutex_task_list);
        if (!tp->can_exit && tp->task_count == 0) {
            pthread_cond_signal(&tp->cond_can_exit);
        }
        // unlock when staying in the loop
        pthread_mutex_unlock(&tp->mutex_task_list);
    }
    tp->thread_count --;
    pthread_cond_signal(&tp->cond_can_exit);
    pthread_mutex_unlock(&tp->mutex_task_list); // unlock when exit <- if tp->can_exit break
    return NULL;
}

thread_pool_t* thread_pool_create(int num_threads, int max_task_count) {
    thread_pool_t *thread_pool = (thread_pool_t *)malloc(sizeof(thread_pool_t));
    thread_pool->can_exit = 0;
    thread_pool->thread_num = num_threads;
    thread_pool->task_count = 0;

    // printf("thread_pool_create: %p\n", thread_pool);
    thread_pool->runner = &thread_pool_runner;
    // printf("set runner to %p\n", thread_pool->runner);

    thread_pool->tid = (pthread_t *)malloc(num_threads * sizeof(pthread_t));
    // printf("allocated thread ids: %p\n", thread_pool->tid);
    thread_pool->task_list = (thread_pool_task_t *)malloc(max_task_count * sizeof(thread_pool_task_t));
    // printf("allocated task list: %p\n", thread_pool->task_list);

    pthread_mutex_init(&thread_pool->mutex_task_list, NULL);
    // printf("initialized mutex: %p\n", &thread_pool->mutex_task_list);
    pthread_cond_init(&thread_pool->cond_task_list, NULL);
    // printf("initialized cond var: %p\n", &thread_pool->cond_task_list);
    pthread_cond_init(&thread_pool->cond_can_exit, NULL);

    int i=0;
    for (i=0; i<num_threads; i++) {
        if (pthread_create(&(thread_pool->tid[i]), NULL, thread_pool->runner, thread_pool) != 0) {
            perror("pthread_create");
            free(thread_pool->tid);
            free(thread_pool);
            free(thread_pool->task_list);
            return NULL;
        }
        // printf("created thread %d with thread id %ld\n", i, thread_pool->tid[i]);
    }

    thread_pool->thread_count = num_threads;
    return thread_pool;
}

// never terminate the pool when joined
void thread_pool_join(thread_pool_t* thread_pool) {
    for (int i=0; i<thread_pool->thread_num; i++) {
        if (pthread_join(thread_pool->tid[i], NULL) != 0) {
            perror("pthread_join");
        }
    }
}

void thread_pool_destroy(thread_pool_t* thread_pool) {
    // printf("destroying thread pool\n");
    pthread_mutex_lock(&thread_pool->mutex_task_list);
    thread_pool->can_exit = 1;
    pthread_cond_broadcast(&thread_pool->cond_task_list);
    pthread_mutex_unlock(&thread_pool->mutex_task_list);

    thread_pool_wait(thread_pool);

    // printf("freeing thread pool\n");
    free(thread_pool->tid);
    free(thread_pool->task_list);
    
    pthread_mutex_destroy(&thread_pool->mutex_task_list);
    pthread_cond_destroy(&thread_pool->cond_task_list);
    pthread_cond_destroy(&thread_pool->cond_can_exit);

    free(thread_pool);
}


void thread_pool_add_task(thread_pool_t* thread_pool, void *(*task_routine) (void *), void *args) {
    pthread_mutex_lock(&thread_pool->mutex_task_list);
    thread_pool_task_t task = {
        .task_routine = task_routine,
        .args = args
    };
    thread_pool->task_list[thread_pool->task_count] = task;
    thread_pool->task_count++;
    pthread_mutex_unlock(&thread_pool->mutex_task_list);
    pthread_cond_signal(&thread_pool->cond_task_list);
}


void thread_pool_wait(thread_pool_t* thread_pool) {
    pthread_mutex_lock(&thread_pool->mutex_task_list);
    while (1) {
        // printf("entering thread_pool_wait loop can_exit = %d, task_count = %d, thread_count = %d\n",
        //         thread_pool->can_exit, thread_pool->task_count, thread_pool->thread_count);
        if ((!thread_pool->can_exit && thread_pool->task_count != 0) || 
                (thread_pool->can_exit && thread_pool->thread_count != 0)) {
            pthread_cond_wait(&thread_pool->cond_can_exit, &thread_pool->mutex_task_list);
        } else {
            // printf("exiting thread_pool_wait loop can_exit = %d, task_count = %d, thread_count = %d\n",
            //     thread_pool->can_exit, thread_pool->task_count, thread_pool->thread_count);
            break;
        }
    }
    // printf("thread_pool_wait loop exited ...\n");
    pthread_mutex_unlock(&thread_pool->mutex_task_list);
}
