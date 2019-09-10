[org 0x7c00]

; Keybaord interrupt is maskable. To Intel 8259 Programmable Interrupt
; Controller, the IRQ number of the keyboard interrupt is 1, which
; means if we were to mask the interrupt, we set the 1st bit of the
; mask (a byte) as 1, i.e, 0x02 (0000 0010 in binary). 
;
; For interrupt request number assignment on PC, see 
; https://en.wikibooks.org/wiki/X86_Assembly/Programmable_Interrupt_Controller
;
; Uncomment the following two statements, and run the code. Does
; the keyboard interrupt work now? 
; 
; mov al, 0x02
; out 21h, al

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
    ; Set interrupt number 0x16 (or 21 in decimal)'s interrupt
    ; service routine as ours. For interrupt 0x16, see
    ;   https://en.wikipedia.org/wiki/INT_16H
    cli
    cld
    mov ax, 0
    mov es, ax
    mov ax, KBD_ISR
    mov [es:21*4], ax
    ; mov ax, 0
    ; mov [es:21*4+2], ax
    mov [es:21*4+2], cs
    sti

    ; print interrupt vector
    mov ax, cs
    mov cl, ah
    call print_byte
    call print_space
    mov cl, al
    call print_byte
    call print_space
    mov ax, KBD_ISR
    mov cl, ah
    call print_byte
    call print_space
    mov cl, al
    call print_byte
    call print_space

    jmp $

%include "../load/print_byte.asm"
%include "../load/print_space.asm"

POS:
    db 0, 0, 0, 0

times 510-($-$$) db 0
dw 0xaa55
