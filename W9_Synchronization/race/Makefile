all: readwritedrive

CFLAGS=-Wall -c
LFLAGS=-lpthread

readwritedrive: readwritedrive.o readwrite.o 
	$(CC) readwritedrive.o readwrite.o -o readwrite $(LFLAGS) 
	
readwritedrive.o: readwritedrive.c
	$(CC) $(CFLAGS) readwritedrive.c 

readwrite.o: readwrite.c
	$(CC) $(CFLAGS) readwrite.c 


 
