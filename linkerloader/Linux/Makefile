all: main

main: main.o sumsine.o
	g++ -o main -lm main.o sumsine.o

.cpp.o:
	$(CXX) -Wall -c $<

clean:
	$(RM) main.o sumsine.o main
