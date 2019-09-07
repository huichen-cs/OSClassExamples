; print a byte in register cl to hex assuming ASCII encoding
;    void * print_byte(char c) 
print_byte:
    pusha

    mov ch, cl
    shr ch, 4
    and ch, 0x0f

    push cx
    mov cl, ch
    call print_low_4bits
    pop cx

    mov ch, cl
    and ch, 0x0f

    push cx
    mov  cl, ch
    call print_low_4bits
    pop cx

    popa
    ret


; print lower 4 bits in register cl to hex assuming ASCII encoding
;    void * print_byte(char c) 
print_low_4bits:
    pusha
    mov ah, 0x0e

    mov ch, cl
    and ch, 0x0f
    cmp ch, 0x09
    jg A_TO_F

    add ch, '0'
    jmp PRINT_CHAR

A_TO_F:
    sub ch, 0x0a
    add ch, 'A'
    jmp PRINT_CHAR

PRINT_CHAR:
    mov al, ch
    int 0x10

    popa
    ret
