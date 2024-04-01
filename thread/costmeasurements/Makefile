all: forktime threadtime clonethreadtime cloneprocesstime

forktime: forktime.c util.c
	$(CC) -Wall $^ -o $@


threadtime: threadtime.c util.c
	$(CC) -Wall $^ -o $@ -lpthread

clonethreadtime: clonethreadtime.c util.c
	$(CC) -Wall $^ -o $@ 

cloneprocesstime: cloneprocesstime.c util.c
	$(CC) -Wall $^ -o $@ 

clean:
	$(RM) cloneprocesstime \
		clonethreadtime \
		threadtime \
		forktime


