all: load0.bin load1.bin load2.bin load3.bin load4.bin load5.bin

load1.bin: load1.asm print_msg.asm
	nasm -f bin load1.asm -o $@

load2.bin: load2.asm print_byte.asm
	nasm -f bin load2.asm -o $@

load3.bin: load3.asm read_disk.asm \
	print_mem.asm print_byte.asm print_space.asm print_line.asm
	nasm -f bin load3.asm -o $@

load4.bin: load4.asm read_disk.asm \
	print_mem.asm print_byte.asm print_space.asm print_line.asm
	nasm -f bin load4.asm -o $@

load5.bin: load5.asm read_disk.asm \
	print_mem.asm print_byte.asm print_space.asm print_line.asm
	nasm -f bin load5.asm -o $@

%.bin: %.asm
	nasm -f bin $< -o $@

clean:
	$(RM) -f *.bin
