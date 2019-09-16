all: piestimator

CFLAGS=-Wall -c
LFLAGS=-lpthread

piestimator: master.o worker.o
	$(CC) -o piestimator master.o worker.o ${LFLAGS}
	
worker.o: worker.c
	$(CC) $(CFLAGS) worker.c 

master.o: master.c
	$(CC) $(CFLAGS) master.c 

runtest1: piestimator testbegin
	time -p ./piestimator 1 80000000 1111 9999

runtest2: piestimator testbegin
	time -p ./piestimator 2 40000000 1111 9999 40000000 3333 4444

runtest4: piestimator testbegin
	time -p ./piestimator 4 20000000 1111 9999 20000000 3333 4444 20000000 3432 4323 20000000 12345 12323

clean:
	$(RM) piestimator master.o worker.o

testbegin:
ifeq ("$(wildcard /usr/bin/time)","")
	@echo "The time util is not found."
	@echo "Run 'apt-get install time' to install time."
	@exit 1
else
	@echo "Test begin"
endif
