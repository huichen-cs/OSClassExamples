[org 0x7c00]
jmp START

KBD_ISR:
    push ax
    push es
    push bx

    ; VGA
    ;   https://en.wikipedia.org/wiki/VGA-compatible_text_mode
    ;   https://en.wikipedia.org/wiki/Video_Graphics_Array#Color_palette
    mov ax, 0xb800
    mov es, ax

    mov bx, [POS]

    mov byte [es:bx], 'C'
    inc bx 
    mov byte [es:bx], 0x01
    inc bx

    mov byte [es:bx], 'I'
    inc bx 
    mov byte [es:bx], 0x02
    inc bx

    mov byte [es:bx], 'S'
    inc bx 
    mov byte [es:bx], 0x03
    inc bx

    mov byte [es:bx], 'C'
    inc bx 
    mov byte [es:bx], 0x04
    inc bx

    mov [POS], bx

    pop bx
    pop es
    pop ax
    iret
    

START:
    ; Set interrupt 0x16 (or 21 in decimal)'s interrupt
    ; service routine as ours. For interrupt 0x16, see
    ;   https://en.wikipedia.org/wiki/INT_16H
    cli
    cld
    mov ax, 0
    mov es, ax
    mov ax, KBD_ISR
    mov [es:21*4], ax
    mov [es:21*4+2], cs
    sti

    jmp $


POS:
    db 0, 0, 0, 0

times 510-($-$$) db 0
dw 0xaa55
