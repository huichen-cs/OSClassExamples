all: readwritedrive

CFLAGS=-Wall -c
LFLAGS=-lpthread

readwritedrive: readwritedrive.o readwrite.o 
	$(CC) $(LFLAGS) readwritedrive.o readwrite.o -o readwrite
	
readwritedrive.o: readwritedrive.c
	$(CC) $(CFLAGS) readwritedrive.c 

readwrite.o: readwrite.c
	$(CC) $(CFLAGS) readwrite.c 


 
