all: ioportex ioportex.s

ioportex: ioportex.c
	gcc -O2 -o ioportex ioportex.c

ioportex.s: ioportex.c
	gcc -S -o ioportex.s ioportex.c
