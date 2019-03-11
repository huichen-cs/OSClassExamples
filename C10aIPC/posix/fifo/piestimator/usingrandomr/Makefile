all: worker master

CFLAGS=-Wall

worker: worker.o
	$(CC) $(CFLAGS) worker.o -o worker

master: master.o
	$(CC) $(CFLAGS) master.o -o master


runtest1: worker master testbegin
	time -p ./master 1 80000000 1111 9999

runtest2: worker master testbegin
	time -p ./master 2 40000000 1111 9999 40000000 3333 4444

runtest4: worker master testbegin
	time -p ./master 4 20000000 1111 9999 20000000 3333 4444 20000000 3432 4323 20000000 12345 12323

clean:
	$(RM) master worker master.o worker.o

testbegin:
ifeq ("$(wildcard /usr/bin/time)","")
	@echo "The time util is not found."
	@echo "Run 'apt-get install time' to install time."
	@exit 1
else
	@echo "Test begin"
endif
