obj-m += chardev.o

all: 
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	$(CC) accesschardev.c -o accesschardev

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	$(RM) accesschardev
