all: scheduledemo

CFLAGS=-Wall 

scheduledemo: scheduledemo.o
	$(CC) -o scheduledemo scheduledemo.o -lpthread

clean:
	$(RM) scheduledemo scheduledemo.o
