all: worker master

CFLAGS=-Wall
worker: worker.c
	$(CC) $(CFLAGS) worker.c -o worker

master: master.c
	$(CC) $(CFLAGS) master.c -o master

runtest1: master testbegin
	time -p ./master 1 80000000 1111 9999

runtest2: master testbegin
	time -p ./master 2 40000000 1111 9999 40000000 3333 4444

runtest4: master testbegin
	time -p ./master 4 20000000 1111 9999 20000000 3333 4444 20000000 3432 4323 20000000 12345 12323

clean:
	$(RM) master.o worker.o master worker

testbegin:
ifeq ("$(wildcard /usr/bin/time)","")
	@echo "The time util is not found.";
	@echo "Run 'apt-get install time' to install time.";
	@exit 1;
else
	@echo "Test begin";
endif



