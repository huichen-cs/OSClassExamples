;
; print_msg_rm.asm
;
; we implement a function with interface
;     void print_msg_rm(char* msg)
; where we pass the argument msg via ds:bx
;
; this function runs in real mode, and as such we can use BIOS int 0x10
;
print_msg_rm:
    pusha           ; push all registers to stack
    mov ah, 0x0e
.loop:
    mov al, [ds:bx]
    cmp al, 0
    je .done
    int 0x10
    inc bx
    jmp .loop
.done:
    popa            ; pop all registers to stack
    ret

