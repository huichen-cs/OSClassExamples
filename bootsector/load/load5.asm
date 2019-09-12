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

mov bx, 0x0000              ; read disk data to es:bx
mov es, bx 
push es
mov bx, 0x9000  
push bx

call read_disk              ; read disk data

mov bx, READ_DISK
call print_msg
call print_line

mov cl, [0x9000] 
call print_byte
call print_space

mov cl, [0x9001] 
call print_byte
call print_space

mov cl, [0x9002] 
call print_byte
call print_space

mov cl, [0x9003] 
call print_byte
call print_space

mov bx, 0x0000  ; push es, bx twice; one set for retf, and one set for the main
mov es, bx 
push es
mov bx, 0x9000  
push bx
push es
push bx
retf


%include "read_disk.asm"
%include "print_byte.asm"
%include "print_mem.asm"
%include "print_msg.asm"
%include "print_space.asm"
%include "print_line.asm"


BOOT_DRIVE:
    db 0

READ_DISK:
    db "Read new program from disk sectors.", 0

times 510 -($-$$) db 0
dw 0xaa55

main:
    pop cx
    pop ds

    mov ah, 0x0e
    mov al, 0x0d
    int 0x10

    mov ah, 0x0e
    mov al, 0x0a
    int 0x10

    mov ax, ANNOUNCEMENT
    sub ax, main
    add ax, cx
    mov bx, ax

    call main_print_msg
    jmp $
    
ANNOUNCEMENT:
    db "New program starts...", 0


main_print_msg:
    pusha           ; push all registers to stack
    mov ah, 0x0e
.LOOP:
    mov al, [ds:bx]
    cmp al, 0
    je .DONE_PRINT_MSG
    int 0x10
    inc bx
    jmp .LOOP
.DONE_PRINT_MSG:
    popa            ; pop all registers to stack
    ret


times 1024-($-$$) db 0
times 512 db 0
