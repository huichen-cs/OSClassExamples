; we implement a function with interface
;     void print_msg(char* msg)
; where we pass the argument msg via ds:bx
print_msg:
    pusha           ; push all registers to stack
    mov ah, 0x0e
.LOOP:
    mov al, [ds:bx]
    cmp al, 0
    je DONE_PRINT_MSG
    int 0x10
    inc bx
    jmp .LOOP
DONE_PRINT_MSG:
    popa            ; pop all registers to stack
    ret

