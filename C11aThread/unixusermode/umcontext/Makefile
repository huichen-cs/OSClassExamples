all: uctxswitch uctxmake uctxswap uctxrestore

CFLAGS=-Wall -c

uctxswitch: uctxswitch.o printctx.o
	$(CC) -o uctxswitch uctxswitch.o printctx.o

uctxmake: uctxmake.o printctx.o
	$(CC) -o uctxmake uctxmake.o printctx.o

uctxrestore: uctxrestore.o
	$(CC) -o uctxrestore uctxrestore.o

uctxswap: uctxswap.o printctx.o
	$(CC) -o uctxswap uctxswap.o printctx.o

clean: 
	$(RM) uctxswitch uctxswitch.o uctxmake uctxmake.o \
		uctxswap uctxswap.o uctxrestore uctxrestore.o \
		printctx.o

