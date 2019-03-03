all: timerdemo pausedemo timeraction timerhandler

CFLAGS=-Wall

timerdemo: timerdemo.o
	$(CC) -o timerdemo timerdemo.o

pausedemo: pausedemo.o
	$(CC) -o pausedemo pausedemo.o

timeraction: timeraction.o
	$(CC) -o timeraction timeraction.o

timerhandler: timerhandler.o
	$(CC) -o timerhandler timerhandler.o

clean: 
	$(RM) timerdemo timerdemo.o \
		pausedemo pausedemo.o \
		timerhandler timerhandler.o \
		timeraction timeraction.o
