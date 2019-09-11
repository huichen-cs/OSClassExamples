all: piestimator

CC=gcc
CFLAGS=-Wall -c
LFLAGS=-lpthread -lgsl -lgslcblas

piestimator: master.o worker.o
	$(CC) -o piestimator master.o worker.o ${LFLAGS}
	
worker.o: worker.c
	$(CC) $(CFLAGS) worker.c 

master.o: master.c
	$(CC) $(CFLAGS) master.c 

runtest1: piestimator 
	time -p ./piestimator 1 80000000 1111 9999

runtest2: piestimator
	time -p ./piestimator 2 40000000 1111 9999 40000000 3333 4444

runtest4: piestimator
	time -p ./piestimator 4 20000000 1111 9999 20000000 3333 4444 20000000 3432 4323 20000000 12345 12323

clean:
	$(RM) piestimator master.o worker.o

#gcc testgsl.c -lgsl -lgslcblas

