all: producerconsumer producerconsumer.s producerconsumer.lst

CFLAGS=-Wall

producerconsumer: producerconsumer.o
	$(CC) -o producerconsumer producerconsumer.o -lrt

producerconsumer.o: producerconsumer.c buffer.h
	$(CC) $(CFLAGS) -c producerconsumer.c

producerconsumer.s: producerconsumer.c
	$(CC) -S -fverbose-asm -g -O2 producerconsumer.c 

producerconsumer.lst: producerconsumer.s
	$(AS) -alhnd producerconsumer.s > producerconsumer.lst



clean:
	$(RM) producerconsumer producerconsumer.o \
		producerconsumer.s producerconsumer.lst
