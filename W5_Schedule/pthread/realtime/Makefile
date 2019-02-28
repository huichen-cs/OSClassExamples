all: rtscheduledemo

CFLAGS=-Wall 

rtscheduledemo: rtscheduledemo.o
	$(CC) -o rtscheduledemo rtscheduledemo.o -lpthread

clean:
	$(RM) rtscheduledemo rtscheduledemo.o
