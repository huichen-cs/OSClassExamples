all: cloneme clonemevm

cloneme: cloneme.c
	$(CC) cloneme.c -o cloneme 

clonemevm: clonemevm.c
	$(CC) -Wno-int-conversion  clonemevm.c -o clonemevm

clean:
	$(RM) cloneme clonemevm
