all: producerconsumer producerconsumer.s

CFLAGS=-Wall

producerconsumer: producerconsumer.o
	$(CC) -o producerconsumer producerconsumer.o -lrt

producerconsumer.s: producerconsumer.c
	$(CC) -fverbose-asm -S producerconsumer.c 



clean:
	$(RM) producerconsumer producerconsumer.o producerconsumer.s
