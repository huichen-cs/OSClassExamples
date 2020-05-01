SHELL=/bin/bash
AFEW=5
ALOT=1000

all: sumsquare

sumsquare: sumsquare.cpp
	$(CXX) $(CFLAGS) -o sumsquare sumsquare.cpp -lpthread

racedemo10few: sumsquare
	for i in {1..$(AFEW)}; do ./sumsquare 10; done | sort | uniq -c

racedemo10lots: sumsquare
	for i in {1..$(ALOT)}; do ./sumsquare 10; done | sort | uniq -c

racedemo20few: sumsquare
	for i in {1..$(AFEW)}; do ./sumsquare 20; done | sort | uniq -c

racedemo20lots: sumsquare
	for i in {1..$(ALOT)}; do ./sumsquare 20; done | sort | uniq -c

clean:
	$(RM) sumsquare
