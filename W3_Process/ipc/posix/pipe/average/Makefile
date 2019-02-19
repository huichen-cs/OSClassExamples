all: average gennumbers pipeoutin


CFLAGS=-Wall

average: average.o
	$(CC) -o average average.o

gennumbers: gennumbers.o
	$(CC) -o gennumbers gennumbers.o

pipeoutin: pipeoutin.o
	$(CC) -o pipeoutin pipeoutin.o

clean:
	$(RM) -f \
		average average.o \
		gennumbers gennumbers.o \
		pipeoutin pipeoutin.o

