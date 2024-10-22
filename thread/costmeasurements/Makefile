all: forktime threadtime clonethreadtime cloneprocesstime \
	forktime2 threadtime2 clonethreadtime2 cloneprocesstime2 

forktime: forktime.c util.c
	$(CC) -Wall $^ -o $@

threadtime: threadtime.c util.c
	$(CC) -Wall $^ -o $@ -lpthread

clonethreadtime: clonethreadtime.c util.c
	$(CC) -Wall $^ -o $@ 

cloneprocesstime: cloneprocesstime.c util.c
	$(CC) -Wall $^ -o $@ 

threadtime2: threadtime2.c util.c
	$(CC) -Wall $^ -o $@ -lpthread

forktime2: forktime2.c util.c
	$(CC) -Wall $^ -o $@

clonethreadtime2: clonethreadtime2.c util.c
	$(CC) -Wall $^ -o $@ 

cloneprocesstime2: cloneprocesstime2.c util.c
	$(CC) -Wall $^ -o $@ 

clean:
	$(RM) cloneprocesstime cloneprocesstime2 \
		clonethreadtime clonethreadtime2 \
		forktime forktime2 \
		threadtime threadtime2 \


