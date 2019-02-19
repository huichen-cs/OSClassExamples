all: waitforchild

CFLAGS=-Wall

waitforchild: waitforchild.o
	$(CC) -o waitforchild waitforchild.o

clean:
	$(RM) -f waitforchild waitforchild.o
