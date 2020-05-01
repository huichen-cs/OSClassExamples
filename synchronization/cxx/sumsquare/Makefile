SHELL=/bin/bash
AFEW=5
ALOT=1000

all: sumsquaremutex sumsquareatomic sumsquarefuture

sumsquaremutex: sumsquaremutex.cpp
	$(CXX) $(CFLAGS) -o sumsquaremutex sumsquaremutex.cpp -lpthread

sumsquareatomic: sumsquareatomic.cpp
	$(CXX) $(CFLAGS) -o sumsquareatomic sumsquareatomic.cpp -lpthread

sumsquarefuture: sumsquarefuture.cpp
	$(CXX) $(CFLAGS) -o sumsquarefuture sumsquarefuture.cpp -lpthread


mutexdemo10few: sumsquaremutex
	for i in {1..$(AFEW)}; do ./sumsquaremutex 10; done | sort | uniq -c

mutexdemo10lots: sumsquaremutex
	for i in {1..$(ALOT)}; do ./sumsquaremutex 10; done | sort | uniq -c

mutexdemo20few: sumsquaremutex
	for i in {1..$(AFEW)}; do ./sumsquaremutex 20; done | sort | uniq -c

mutexdemo20lots: sumsquaremutex
	for i in {1..$(ALOT)}; do ./sumsquaremutex 20; done | sort | uniq -c

atomicdemo10few: sumsquareatomic
	for i in {1..$(AFEW)}; do ./sumsquareatomic 10; done | sort | uniq -c

atomicdemo10lots: sumsquareatomic
	for i in {1..$(ALOT)}; do ./sumsquareatomic 10; done | sort | uniq -c

atomicdemo20few: sumsquareatomic
	for i in {1..$(AFEW)}; do ./sumsquareatomic 20; done | sort | uniq -c

atomicdemo20lots: sumsquareatomic
	for i in {1..$(ALOT)}; do ./sumsquareatomic 20; done | sort | uniq -c

futuredemo10few: sumsquarefuture
	for i in {1..$(AFEW)}; do ./sumsquarefuture 10; done | sort | uniq -c

futuredemo10lots: sumsquarefuture
	for i in {1..$(ALOT)}; do ./sumsquarefuture 10; done | sort | uniq -c

futuredemo20few: sumsquarefuture
	for i in {1..$(AFEW)}; do ./sumsquarefuture 20; done | sort | uniq -c

futuredemo20lots: sumsquarefuture
	for i in {1..$(ALOT)}; do ./sumsquarefuture 20; done | sort | uniq -c

clean:
	$(RM) sumsquaremutex sumsquarefuture sumsquareatomic
