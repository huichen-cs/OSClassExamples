all: sum

CFLAGS=-Wall

sum: sum_main.o part_sum.o util.o
	$(CC) -lpthread -o sum sum_main.o part_sum.o util.o

clean: 
	$(RM) -f sum_main.o part_sum.o util.o sum


