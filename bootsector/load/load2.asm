[org 0x7c00]
; query disk drive parameters
; 
; load2.asm
;
; using PC BIOS's 0x13 interrupt
; See
;   https://en.wikipedia.org/wiki/INT_13H#INT_13h_AH=08h:_Read_Drive_Parameters

READ_DISK:

mov ah, 0x08
mov dl, 0x80    ; 1st HDD
mov ax, 0
mov es, ax
mov di, ax
int 0x13

jc .DISK_ERROR  ; using local label. local labels start from "."

push cx

push bx
mov bx, DISK_NO
call print_msg
mov cl, dl
call print_byte
pop bx

call print_line

push bx
mov bx, HEAD_IDX
call print_msg
mov cl, dh
call print_byte
pop bx

call print_line

pop cx

push cx

push bx
mov bx, SECTOR_NUM
call print_msg
pop bx

mov cl, ch
call print_byte
call print_space
pop cx
call print_byte

pop cx

jmp $    


.DISK_ERROR:
    mov bx, DISK_ERROR_MSG
    call print_msg
    
    jmp $
    

%include "print_byte.asm"
%include "print_msg.asm"
%include "print_line.asm"
%include "print_space.asm"

DISK_ERROR_MSG:
    db "Disk error", 0

DISK_NO:
    db "DISK # (hex): ", 0
HEAD_IDX:
    db "HEAD INDEX (hex): ", 0
SECTOR_NUM:
    db "CYL/SEC NUMBERS (hex): ", 0

times 510-($-$$) db 0
dw 0xaa55

times 512 db 0
times 512 db 0
