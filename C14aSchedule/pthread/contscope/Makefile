all: contscopedemo

CC=gcc
CFLAGS=-Wall 

contscopedemo: contscopedemo.o
	$(CC) -o contscopedemo contscopedemo.o -lpthread

clean:
	$(RM) contscopedemo contscopedemo.o
