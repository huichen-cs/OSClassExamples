all: ordinarypipe average gennumbers pipeoutin


CFLAGS=-Wall

ordinarypipe: ordinarypipe.o
	$(CC) -o ordinarypipe ordinarypipe.o

average: average.o
	$(CC) -o average average.o

gennumbers: gennumbers.o
	$(CC) -o gennumbers gennumbers.o

pipeoutin: pipeoutin.o
	$(CC) -o pipeoutin pipeoutin.o

clean:
	$(RM) -f \
		ordinarypipe ordinarypipe.o \
		average average.o \
		gennumbers gennumbers.o \
		pipeoutin pipeoutin.o

