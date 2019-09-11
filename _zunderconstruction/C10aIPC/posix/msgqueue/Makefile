all: mqreceiver mqsender

CFLAGS=-Wall

mqreceiver:mqreceiver.o
	$(CC) -o mqreceiver mqreceiver.o -lrt

mqsender:mqsender.o
	$(CC) -o mqsender mqsender.o -lrt

clean:
	$(RM) mqsender mqreceiver mqsender.o mqreceiver.o
