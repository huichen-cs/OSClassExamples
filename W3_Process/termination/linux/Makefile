all: normal error fatal fatalsignaled killprocess

CFLAGS=-Wall

normal: normal.c
	$(CC) $(CFLAGS) normal.c -o normal

error: error.c
	$(CC) $(CFLAGS) error.c -o error

fatal: fatal.c
	$(CC) $(CFLAGS) fatal.c -o fatal

fatalsignaled: fatalsignaled.c
	$(CC) $(CFLAGS) fatalsignaled.c -o fatalsignaled

killprocess: killprocess.c
	$(CC) $(CFLAGS) killprocess.c -o killprocess

trace: normal
	strace ./normal
