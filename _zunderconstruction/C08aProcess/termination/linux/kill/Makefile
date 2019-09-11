all: killprocess

CFLAGS=-Wall

killprocess: killprocess.o
	$(CC) $(CFLAGS) -o killprocess killprocess.o


clean:
	$(RM) -f killprocess.o  killprocess
