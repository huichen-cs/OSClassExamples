all: pooltest


pooltest: pooltest.c threadpool.c
	$(CC) -I. pooltest.c threadpool.c -lpthread -o pooltest

