all: echoclient echoserver

CFLAGS=-Wall
LDFLAGS=-lpthread
echoclient: echoclient.c

echoserver: echoserver.c
	$(CC) $(CFLAGS) -o echoserver echoserver.c $(LDFLAGS)

clean:
	$(RM) echoclient echoserver
