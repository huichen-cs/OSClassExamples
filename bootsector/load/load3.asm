mov ax, 0x7c0
mov ds, ax
mov bx, DATA
mov cl, 64
call print_mem

jmp $


%include "print_mem.asm"
%include "print_byte.asm"
%include "print_space.asm"
%include "print_line.asm"

DATA:
times 8  db 0x36, 0x72, 0xae, 0xff, 0x3a, 0x11, 0x12, 0x13

times 510-($-$$) db 0
dw 0xaa55

