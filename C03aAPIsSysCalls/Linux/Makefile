all: copyfile

copyfile: copyfile.o
	$(CXX) copyfile.o -o copyfile

copyfile.o: copyfile.cpp
	$(CXX) -c copyfile.cpp

clean: 
	$(RM) copyfile copyfile.o
