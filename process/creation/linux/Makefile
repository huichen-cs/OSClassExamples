all: worker master

CFLAGS=-Wall
worker: worker.c
	$(CC) $(CFLAGS) worker.c -o worker

master: master.c
	$(CC) $(CFLAGS) master.c -o master

