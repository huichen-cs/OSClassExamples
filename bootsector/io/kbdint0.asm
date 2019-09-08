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
    push cx
    ; read scan code
    in al, 0x60
    mov cl, al
    call print_byte
    call print_space

    mov byte ah, [line_counter]
    inc ah
    mov byte [line_counter], ah
    and ah, 0x01
    jz LINE_BREAK
    jmp EXIT_ISR

LINE_BREAK:
    call print_line

EXIT_ISR:
    pop cx
    pop ax
    iret
    
%include "../load/print_byte.asm"
%include "../load/print_space.asm"
%include "../load/print_line.asm"

line_counter:
    db 0


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
    mov [es:21*4+2], cs
    sti

    jmp $


POS:
    db 0, 0, 0, 0

times 510-($-$$) db 0
dw 0xaa55
