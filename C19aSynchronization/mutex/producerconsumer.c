/**
 * This is the sample program in page 138,
 *  Andrew S. Tanenbaum and Herbert Bos. 2014. Modern Operating Systems (4th
 *  ed.). Prentice Hall Press, Upper Saddle River, NJ, USA. 
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

#define MAX 1000
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;

void *producer(void *ptr) {
    int i;

    for (i=1; i<=MAX; i++) {
        pthread_mutex_lock(&the_mutex);
        while (buffer != 0) {
            pthread_cond_wait(&condp, &the_mutex);
        }
        buffer = i;
        pthread_cond_signal(&condc);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

void *consumer(void *ptr) {
    int i;

    for (i=1; i<=MAX; i++) {
        pthread_mutex_lock(&the_mutex);
        while (buffer == 0) {
            pthread_cond_wait(&condc, &the_mutex);
        }
        buffer = 0;
        pthread_cond_signal(&condp);
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    pthread_t producer_thread, consumer_thread;

    pthread_mutex_init(&the_mutex, 0);
    pthread_cond_init(&condc, 0);
    pthread_cond_init(&condp, 0);

    pthread_create(&consumer_thread, 0, consumer, 0);
    pthread_create(&producer_thread, 0, producer, 0);
    
    pthread_join(producer_thread, 0);
    pthread_join(consumer_thread, 0);

    pthread_cond_destroy(&condc);
    pthread_cond_destroy(&condp);
    pthread_mutex_destroy(&the_mutex);

    return EXIT_SUCCESS;
}

