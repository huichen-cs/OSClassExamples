[org 0x7c00]

mov bp, 0x9000
mov sp, bp

mov bx, MSG_REAL_MODE
call print_msg_rm

call switch_to_pm

jmp $

%include "print_msg_rm.asm"
%include "gdt0.asm"
%include "print_msg_pm.asm"
%include "switchpm.asm"

[bits 32]
begin_pm:
    mov ebx, MSG_PROT_MODE
    call print_msg_pm

    jmp $

MSG_REAL_MODE:
     db "Started in 16-bit real mode", 0

MSG_PROT_MODE:
    db "Switched to 32-bit protected mode", 0

times 510-($-$$) db 0
dw 0xaa55

