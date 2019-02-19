all: parent.exe child.exe

parent.exe: parent.obj
	$(CC) parent.obj /Feparent.exe

child.exe: child.obj
	$(CC) child.obj /Fechild.exe

clean:
	del parent.obj child.obj parent.exe child.exe
