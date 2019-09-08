; http://www-ug.eecg.toronto.edu/msl/nios_devices/datasheets/PS2%20Keyboard%20Protocol.htm
; http://bochs.sourceforge.net/techspec/PORTS.LST

; disable keyboard interrupt
mov al, 0x02
out 21h, al

mov cx, 0
KBD_READ:
    push cx 
LOOP:
    ; query keybard status
    in al, 0x64
    mov cl, al
    and al, 0x01
    jz LOOP

    ; read scan code
    in al, 0x60

    ; print scan code
    ; for PS/2 scan code table, see
    ;   http://www.vetra.com/scancodes.html
    mov cl, al
    call print_byte
    call print_space

    pop cx
    inc cx
    and cx, 0x01
    jnz KBD_READ
    call print_line

    jmp KBD_READ


jmp $

%include "../load/print_byte.asm"
%include "../load/print_space.asm"
%include "../load/print_line.asm"
times 510-($-$$) db 0
dw 0xaa55
