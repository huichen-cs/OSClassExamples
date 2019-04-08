all: producerconsumer producerconsumer.s

CFLAGS=-Wall

producerconsumer: producerconsumer.o
	$(CC) -o producerconsumer producerconsumer.o -lrt

producerconsumer.o: producerconsumer.c buffer.h
	$(CC) $(CFLAGS) -c producerconsumer.c

producerconsumer.s: producerconsumer.c
	$(CC) -fverbose-asm -S producerconsumer.c 



clean:
	$(RM) producerconsumer producerconsumer.o producerconsumer.s
