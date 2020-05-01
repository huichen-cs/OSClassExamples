all: pagetable

pagetable: pagetable.c
	$(CC) -o $@ $<

demo: pagetable
	sudo ./pagetable 1

clean:
	$(RM) pagetable
