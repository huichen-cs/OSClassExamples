all: worker master

CFLAGS=-Wall
worker: worker.c
	$(CC) $(CFLAGS) worker.c -o worker

master: master.c
	$(CC) $(CFLAGS) master.c -o master

runtest2: worker master
	./master 2 100000 1111 9999 200000 3333 4444

runtest4: worker master
	./master 4 100000 1111 9999 200000 3333 4444 300000 3432 4323 200000 12345 12323

