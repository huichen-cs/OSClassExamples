all: sumall printall

CFLAGS=-Wall

sumall: sumall.cpp
	$(CXX) -fopenmp sumall.cpp -o sumall

printall: printall.cpp
	$(CXX) -fopenmp printall.cpp -o printall

runprintall_1:
	OMP_NUM_THREADS=1 ./printall

runprintall_4:
	OMP_NUM_THREADS=4 ./printall

runsumall_1:
	OMP_NUM_THREADS=1 time ./sumall 200000000

runsumall_2:
	OMP_NUM_THREADS=2 time ./sumall 200000000

runsumall_4:
	OMP_NUM_THREADS=4 time ./sumall 200000000

clean: 
	$(RM) sumall printall


