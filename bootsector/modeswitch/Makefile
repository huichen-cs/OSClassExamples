all:  boot0.bin

boot0.bin: boot0.asm gdt0.asm print_msg_pm.asm print_msg_rm.asm switchpm.asm
	nasm -f bin boot0.asm -o boot0.bin
