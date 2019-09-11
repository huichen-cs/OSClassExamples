all: CopyFile.exe

CFLAGS = /W3 /EHsc

CopyFile.exe: CopyFile.obj
	$(CXX) CopyFile.obj /FeCopyFile.exe

CopyFile.obj: CopyFile.cpp
	$(CXX)  $(CFLAGS) /c CopyFile.cpp

clean:
	$(RM) CopyFile.exe CopyFile.obj
