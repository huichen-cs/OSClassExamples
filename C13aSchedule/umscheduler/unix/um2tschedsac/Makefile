all: umthreaddemo

CFLAGS=-Wall -g

umthreaddemo: umthreaddemo.o printctx.o
	$(CC) -o umthreaddemo umthreaddemo.o  printctx.o

clean:
	$(RM) umthreaddemo umthreaddemo.o printctx.o
