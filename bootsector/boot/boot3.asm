mov ah, 0x0e
mov bx, HELLO_MSG
add bx, 0x7c00

LOOP:
    mov al, [bx]
    cmp al, 0
    je DONE_PRINT
    int 0x10
    inc bx
    jmp LOOP

DONE_PRINT:
    jmp $ 

HELLO_MSG :
    db 'Hello, World!', 0 ;

times 510-($-$$) db 0 
dw 0xaa55 

