/**
 * This is a revision of the sample program in page 138,
 *  Andrew S. Tanenbaum and Herbert Bos. 2014. Modern Operating Systems (4th
 *  ed.). Prentice Hall Press, Upper Saddle River, NJ, USA. 
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <pthread.h>

/* the bounded buffer */
#define NUM_PRODUCED 10000
#define BUFFER_SIZE 4096
static int buffer[BUFFER_SIZE];
static int in;
static int out;
static int counter;
static pthread_mutex_t the_mutex;
static pthread_cond_t condc, /* consumer waits */ 
                      condp; /* producer waits */

void *producer(void *ptr) {
    int i;

    for (i=0; i<NUM_PRODUCED; i++) {
        int nextproduced = i;

        pthread_mutex_lock(&the_mutex);

        while (counter == BUFFER_SIZE) {
            /* the producer thread must wait when the buffer is full */
            pthread_cond_wait(&condp, &the_mutex); 
        }

        buffer[in] = nextproduced;
        in = (in + 1) % BUFFER_SIZE;
        counter ++;

        pthread_cond_signal(&condc); /* wake up the consumer if it's sleeping */
        pthread_mutex_unlock(&the_mutex);
    }
    pthread_exit(0);
}

void *consumer(void *ptr) {
    int i, nextconsumed, sum = 0;

    for (i=0; i<NUM_PRODUCED; i++) {

        pthread_mutex_lock(&the_mutex);

        while (counter == 0) {
            /* the consumer thread must wait when the buffer is empty */
            pthread_cond_wait(&condc, &the_mutex); 
        }

        nextconsumed = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        counter --;

        pthread_cond_signal(&condp); /* wake up the producer if it's sleeping */
        pthread_mutex_unlock(&the_mutex);
        
        /* consume the item */
        sum += nextconsumed;
    }

    printf("The sum is %d\n", sum);
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    pthread_t producer_thread, consumer_thread;

    counter = 0; in = 0; out = 0;
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

