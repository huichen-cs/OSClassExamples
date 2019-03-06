all: cloneuts clonepipe

CFLAGS=-Wall
 
cloneuts: cloneuts.o
	$(CC) -o cloneuts cloneuts.o

clonepipe: clonepipe.o
	$(CC) -o clonepipe clonepipe.o

clean:
	$(RM) cloneuts cloneuts.o clonepipe clonepipe.o
