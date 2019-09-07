all: boot0.bin boot1.bin boot2.bin boot3.bin boot4.bin boot5.bin

%.bin: %.asm
	nasm -f bin $< -o $@

clean:
	$(RM) -f *.bin
