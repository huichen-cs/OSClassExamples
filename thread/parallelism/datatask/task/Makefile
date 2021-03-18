all: main

CFLAGS=-Wall

main: main.c tasks.c util.c
	$(CC) -lpthread -lm -o main main.c tasks.c util.c

clean: 
	$(RM) -f main.o tasks.o util.o main


