all: piestimator

CFLAGS=-Wall -c
LFLAGS=-lpthread

piestimator: piestimator.o worker.o
	$(CC) $(LFLAGS) piestimator.o worker.o -o piestimator
	
worker.o: worker.c
	$(CC) $(CFLAGS) worker.c 

piestimator.o: piestimator.c
	$(CC) $(CFLAGS) piestimator.c 

runtest2pcs: piestimator
	./piestimator 2 100000000 1111 9999 10000000 3333 4444 pcs

runtest2scs: piestimator
	./piestimator 2 100000000 1111 9999 10000000 3333 4444 scs

runtest4pcs: piestimator
	./piestimator 4 100000 1111 9999 200000 3333 4444 300000 3432 4323 200000 12345 12323 pcs

runtest4scs: piestimator
	./piestimator 4 100000 1111 9999 200000 3333 4444 300000 3432 4323 200000 12345 12323 scs
 
