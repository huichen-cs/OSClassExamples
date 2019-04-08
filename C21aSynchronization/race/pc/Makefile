all: producerconsumer

CFLAGS=-Wall

producerconsumer: producerconsumer.o
	$(CC) -o producerconsumer producerconsumer.o -lrt

clean:
	$(RM) producerconsumer producerconsumer.o
