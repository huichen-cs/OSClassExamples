[org 0x7c00]

START:

mov [BOOT_DRIVE], dl

mov bp, 0x8000
mov sp, bp

mov ah, 0x00                ; resetting disk 
int 0x13 


; pass arguments
mov ah, 0x02                ; int 13h function 02
mov al, 0x02                ; read 2 sectors
push ax

mov ch, 0x00                ; cylinder no.
mov cl, 0x02                ; sector no. (sector 1 is boot sector)
push cx

mov dh, 0x00                ; head no.
mov dl, [BOOT_DRIVE]        ; drive no.
push dx

push es                     ; read disk data to es:bx
mov bx, 0x9000
push bx

call read_disk              ; read disk data


mov cl, [0x9000]
call print_byte
call print_space
mov cl, [0x9000+512]
call print_byte

jmp $

%include "read_disk.asm"
%include "print_byte.asm"
%include "print_mem.asm"
%include "print_msg.asm"
%include "print_space.asm"
%include "print_line.asm"


BOOT_DRIVE:
    db 0

times 510 -($-$$) db 0
dw 0xaa55

times 512 db 0xab
times 512 db 0xba


