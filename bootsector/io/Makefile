all: kbdpoll0.bin kbdint0.bin

%.bin: %.asm
	nasm -f bin $< -o $@

clean:
	$(RM) -f *.bin
