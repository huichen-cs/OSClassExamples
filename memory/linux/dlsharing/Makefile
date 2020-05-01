all: driver1 driver2 libvector.so driver1dl driver2dl

CFLAGS=-Wall -c -static

runstatic:
	./driver1 &
	./driver2 &

rundl:
	LD_LIBRARY_PATH=./ ./driver1dl &
	LD_LIBRARY_PATH=./ ./driver2dl &

driver1dl: driver1.o libvector.so
	$(CXX) -L./ -lvector -o driver1dl driver1.o /usr/lib/gcc/i686-linux-gnu/8/libstdc++.a 

driver2dl: driver2.o libvector.so
	$(CXX) -L./ -o driver2dl driver2.o -lvector 

driver1: driver1.o vector.o
	$(CXX) -static -o driver1 driver1.o vector.o

driver1.o: driver1.cpp
	$(CXX) $(CFLAGS) -o driver1.o driver1.cpp

driver2: driver2.o vector.o
	$(CXX) -static -o driver2 driver2.o vector.o

driver2.o: driver2.cpp
	$(CXX) $(CFLAGS) -o driver2.o driver2.cpp

libvector.so: vector.o
	$(CXX) -shared -o libvector.so vector.o

vector.o: vector.cpp
	$(CXX) $(CFLAGS) -fPIC -o vector.o vector.cpp

clean:
	$(RM) vector.o driver1.o \
		driver1.o driver1 driver2.o driver2  \
		libvector.so \
		driver1dl driver2dl

