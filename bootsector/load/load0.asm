
mov ax, 0x7c0
mov ds, ax
mov bx, MSG

mov ah, 0x0e

LOOP:
    mov al,[ds:bx]
    cmp al, 0
    je DONE_PRINT
    int 0x10
    inc bx
    jmp LOOP

DONE_PRINT:
    jmp $

MSG:
    db "Hello, Segment!", 0

times 510-($-$$) db 0
dw 0xaa55
