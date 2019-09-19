all:  boot32bits0.bin

boot32bits0.bin: boot32bits0.asm \
	gdt0.asm print_msg_pm.asm print_msg_rm.asm switchpm.asm
	nasm -f bin boot32bits0.asm -o boot32bits0.bin
