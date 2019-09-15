;
; print_msg_pm.asm
;
; function
;   void print_msg_pm(char *msg)
; where we pass address to msg via register ebx
;
[bits 32]

VGA_TEXT_MEM_BASE equ 0xb8000
TEXT_ATTR         equ 0x0f

print_msg_pm:
    pusha
    mov edx, VGA_TEXT_MEM_BASE
    
.loop:
    mov al, [ebx]   ; msg base
    mov ah, TEXT_ATTR

    cmp al, 0
    je .done

    mov [edx], ax

    add ebx, 1      ; next char
    add edx, 2      ; next char position in VGA text memory

    jmp .loop

.done:
    popa
    ret

