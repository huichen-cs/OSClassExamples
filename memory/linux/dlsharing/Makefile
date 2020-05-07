SHELL=/bin/bash

all: driver1 driver2 libvector.so driver1dl driver2dl

BUILD_MSG = @echo -n -e "Building $@ from $< ... "
DL_COMPILE_CMD = @$(CXX) $(CFLAGS) -fPIC -o $@ $<
ST_COMPILE_CMD = @$(CXX) $(CFLAGS) -o $@ $<
MAKE_DLLIB_CMD = @$(CXX) -shared -o libvector.so vector.o
DL_BUILD_CMD = @$(CXX) -L./ -lvector -o $@ $< 
ST_BUILD_CMD = @$(CXX) -static -o $@ $< vector.o
BAD_MSG = echo "failed $$?"; exit 1
OK_MSG = echo "OK $$?"; exit 0


CFLAGS=-Wall -c -static

runstatic:
	@echo "Shared library dependencies for driver1dl and driver2dl:"
	@echo "driver1:"
	@ldd ./driver1 || exit 0
	@echo "driver2:"
	@ldd ./driver2 || exit 0
	./driver1 &
	./driver2 &

rundl:
	@echo "Shared library dependencies for driver1dl and driver2dl:"
	LD_LIBRARY_PATH=./ ldd ./driver1dl
	LD_LIBRARY_PATH=./ ldd ./driver2dl
	LD_LIBRARY_PATH=./ ./driver1dl &
	LD_LIBRARY_PATH=./ ./driver2dl &

driver1dl: driver1.o libvector.so
	$(BUILD_MSG)
	$(DL_BUILD_CMD) || ($(BAD_MSG)) && ($(OK_MSG))

driver2dl: driver2.o libvector.so
	$(BUILD_MSG)
	$(DL_BUILD_CMD) || ($(BAD_MSG)) && ($(OK_MSG))

driver1: driver1.o vector.o
	$(BUILD_MSG)
	$(ST_BUILD_CMD) || ($(BAD_MSG)) && ($(OK_MSG))

driver2: driver2.o vector.o
	$(BUILD_MSG)
	$(ST_BUILD_CMD) || ($(BAD_MSG)) && ($(OK_MSG))

driver1.o: driver1.cpp
	$(BUILD_MSG)
	$(ST_COMPILE_CMD) || ($(BAD_MSG)) && ($(OK_MSG))

driver2.o: driver2.cpp
	$(BUILD_MSG)
	$(ST_COMPILE_CMD) || ($(BAD_MSG)) && ($(OK_MSG))

libvector.so: vector.o
	$(BUILD_MSG)
	$(MAKE_DLLIB_CMD) || ($(BAD_MSG)) && ($(OK_MSG))

vector.o: vector.cpp
	$(BUILD_MSG)
	$(DL_COMPILE_CMD) || ($(BAD_MSG)) && ($(OK_MSG))

clean:
	$(RM) vector.o driver1.o \
		driver1.o driver1 driver2.o driver2  \
		libvector.so \
		driver1dl driver2dl

