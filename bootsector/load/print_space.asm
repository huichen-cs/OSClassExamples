print_space:
    pusha

    mov ah, 0x0e
    mov al, ' '
    int 0x10

    popa
    ret
