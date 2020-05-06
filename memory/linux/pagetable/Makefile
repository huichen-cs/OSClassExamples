SHELL=/bin/bash

all: pagetable

CFLAGS=-Wall
COMPILE_MSG=@echo -n -e "Compiling $< ..."
COMPILE_C=@$(CC) $(CFLAGS) -o $@ $< $(MAKEDEP) $(INCLUDES)

pagetable: pagetable.c
	$(COMPILE_MSG)
	$(COMPILE_C) || (echo "failed $$?"; exit 1) && (echo " OK"; exit 0)

demo: pagetable
	sudo ./pagetable 1

clean:
	$(RM) pagetable
