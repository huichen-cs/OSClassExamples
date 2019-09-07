mov bx, 3
mov ah, 0x0e 

print_hello:
    mov al, 'H'
    int 0x10

    mov al, 'e'
    int 0x10

    mov al, 'l'
    int 0x10

    mov al, 'l'
    int 0x10

    mov al, 'o'
    int 0x10

    mov al, ' '
    int 0x10

    dec bx
    cmp bx, 0
    jne print_hello

jmp $ 

times 510-($-$$) db 0 
dw 0xaa55 

