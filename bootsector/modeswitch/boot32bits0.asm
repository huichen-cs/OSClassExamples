[org 0x7c00]

; set up real-mode stack
mov bp, 0x9000  
mov sp, bp

; print a message in real mode
mov bx, MSG_REAL_MODE
call print_msg_rm

; switch to protected mode
call switch_to_pm

; we will never return here if the above is successful
jmp $

%include "print_msg_rm.asm"
%include "gdt0.asm"
%include "print_msg_pm.asm"
%include "switchpm.asm"     ; begin_pm is a callback, and to be called therein

[bits 32]
main_pm:
    ; do something useful, such as, print a message in protected mode
    mov ebx, MSG_PROT_MODE
    call print_msg_pm

    jmp $

MSG_REAL_MODE:
     db "Started in 16-bit real mode", 0

MSG_PROT_MODE:
    db "Switched to 32-bit protected mode", 0

times 510-($-$$) db 0
dw 0xaa55

