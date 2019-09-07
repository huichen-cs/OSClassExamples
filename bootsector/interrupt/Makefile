all: int0.bin

%.bin: %.asm
	nasm -f bin $< -o $@

clean:
	$(RM) -f *.bin
