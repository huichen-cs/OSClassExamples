#ifndef __READ_WRITE__
#define __READ_WRITE__

struct thread_info {
    pthread_t thread_id;        /* ID returned by pthread_create() */
    int       thread_num;       /* Application-defined thread # */
    int       *item;
};

void *readwrite();


#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_warn(msg) \
    do { fprintf(stderr, "%s\n", msg); } while (0)

#define handle_warn_en(en, msg) \
    do { errno = en; perror(msg); } while (0)

#endif
