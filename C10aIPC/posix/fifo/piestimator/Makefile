all: worker master

CFLAGS=-Wall
worker: worker.c
	$(CC) $(CFLAGS) worker.c -o worker

master: master.c
	$(CC) $(CFLAGS) master.c -o master

runtest1: worker master
	./master 1 80000000 1111 9999

runtest2: worker master
	./master 2 40000000 1111 9999 40000000 3333 4444

runtest4: worker master
	./master 4 20000000 1111 9999 20000000 3333 4444 20000000 3432 4323 20000000 12345 12323

