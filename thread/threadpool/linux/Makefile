all: pooltest

.c.o:
	$(CC) -I. -c $<

pooltest: pooltest.o threadpool.o
	$(CC) -I. pooltest.o threadpool.o -lpthread -o pooltest

clean:
	$(RM) pooltest pooltest.o threadpool.o

