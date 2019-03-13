/**
 * This program is from 
 *  Silberschatz, Abraham, Greg Gagne, and Peter B. Galvin. Operating system
 *  concepts. Wiley, 2018
 */

#include <stdio.h> 
#include <unistd.h>
#include <pthread.h> 

#define NUM_THREADS 5 

static void *runner(void *param);

int main(int argc, char *argv[]) { 
   int i, scope, change = 0;
   pthread_t tid[NUM_THREADS]; 
   pthread_attr_t attr; 

   if (argc > 1) {
       change = 1;
   }

   /* get the default attributes */ 
   pthread_attr_init(&attr); 

   /* first inquire on the current scope */
   if (pthread_attr_getscope(&attr, &scope) != 0) {
      fprintf(stderr, "Unable to get scheduling scope\n"); 
   } 
   

   
   /* set the scheduling algorithm to PCS or SCS */ 
   if (scope == PTHREAD_SCOPE_PROCESS) {
       printf("The default contention scope is PTHREAD_SCOPE_PROCESS\n"); 
       if (change) {
           if (pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM) != 0) {
               fprintf(stderr, "Failed to set scope as PTHREAD_SCOPE_SYSTEM\n");
           } else {
               printf("Successfully set scope as PTHREAD_SCOPE_SYSTEM\n");
           }
       }
   } else if (scope == PTHREAD_SCOPE_SYSTEM) {
       printf("The default contention scope is PTHREAD_SCOPE_SYSTEM\n"); 
       if (change) {
           if (pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS) != 0) {
               fprintf(stderr, "Failed to set scope as PTHREAD_SCOPE_PROCESS\n");
           } else {
               printf("Successfully set scope as PTHREAD_SCOPE_PROCESS\n");
           }
       }
   } else {
       fprintf(stderr, "Illegal scope value.\n"); 
       if (change) {
           if (pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM) != 0) {
               fprintf(stderr, "Failed to set scope as PTHREAD_SCOPE_SYSTEM\n");
           } else {
               printf("Successfully set scope as PTHREAD_SCOPE_SYSTEM\n");
           }
       }
   }


   /* create the threads */
   for (i = 0; i < NUM_THREADS; i++) {
      pthread_create(&tid[i],&attr,runner,NULL); 
   }
   /* now join on each thread */
   for (i = 0; i < NUM_THREADS; i++) {
      pthread_join(tid[i], NULL); 
   }

   return 0;
} 

/* Each thread will begin control in this function */ 
static void *runner(void *param) { 
   /* do some work ... */ 
   pid_t ppid = getppid();
   pid_t pid = getpid();
   pthread_t tid = pthread_self();
   printf("ppid = %lu pid = %lu tid = %lu\n", (unsigned long)ppid, 
          (unsigned long)pid, (unsigned long)tid);
   pthread_exit(0); 
} 

