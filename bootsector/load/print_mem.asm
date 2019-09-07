; print memory in hex byte by byte separated by a space
;   void print_mem(void *, short num);
; the parameter is passed via registers ds:bx and cl
print_mem:
    pusha
    mov ah, 0x0e
    
    cmp cl, 0
    je NOTHING_TO_PRINT

    xor ch, ch
LOOP:
    push cx
    mov cl, [ds:bx] 
    call print_byte
    pop cx
    inc bx
    dec cl
    inc ch

    cmp cl, 0
    je NOTHING_TO_PRINT

    and ch, 0x0f
    cmp ch, 0
    jnz DO_PRINT_SPACE 
    call print_line
    jmp LOOP

DO_PRINT_SPACE:
    call print_space
    jmp LOOP

NOTHING_TO_PRINT:
    popa
    ret
