;
; print_msg_pm.asm
;
; function
;   void print_msg_pm(char *msg)
; where we pass address to msg via register ebx
;
; since there is no direct BIOS access in protected mode, we directly
; write VGA device controller memory. The VGA device by default is in
; text mode whose memory's base address is 0xb8000 where one character
; uses two bytes, the first byte is character and the second attributes,
; such as foreground and background colors
;
[bits 32]

VGA_TEXT_MEM_BASE equ 0xb8000
TEXT_ATTR         equ 0x4f

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

