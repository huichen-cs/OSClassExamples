; read disk sectors with prototype
;   uint16 read_disk(
;       uint16 offset,
;       uint16 segment,
;       uint8 sector_count, 
;       uint8 cylinder, 
;       uint8 sector, 
;       uint8 head, 
;       uint8 drive)
; the subroutine expects the parameters passed in stack 
;       offset
;       segment
;       cylinder sector
;       head rive
;       0000 0010b count
;       
; return value is also in stack
;       uint16
; the subroutine reads disk via PC BIOS int13h
; See https://en.wikipedia.org/wiki/INT_13H
;
read_disk:
;   for near call
;      ip on the top of the stack
    push ax
    push cx
    push dx
    push bp

;   parameters are at sp+10
    mov bp, sp 
    mov bx, [bp+10]         ; disk data to es:bx
    mov ax, [bp+12]
    mov es, ax

    mov dx, [bp+14]         ; dh dl are head no. and drive no.
    mov cx, [bp+16]         ; ch cl are cylinder and sector no.'s

    mov ax, [bp+18]
    mov ah, 0x02

    push ax
    int 0x13
    pop dx

    jc .DISK_ERROR

    cmp dh, al
    jne .DISK_SHORT_READ

    pop bp
    pop dx
    pop cx
    pop ax

    sub bp, 2*5
    ret


.DISK_ERROR:
    mov bx, DISK_ERROR_MSG
    call print_msg

    jmp $

.DISK_SHORT_READ:
    mov bx, SHORT_READ_MSG
    call print_msg

    jmp $

DISK_ERROR_MSG:
    db "Disk read error!", 0

SHORT_READ_MSG:
    db "Disk read error, short read!", 0

