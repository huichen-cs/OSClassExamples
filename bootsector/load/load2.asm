mov cl, 0xae
call print_byte
jmp $

%include "print_byte.asm"

times 510-($-$$) db 0
dw 0xaa55
