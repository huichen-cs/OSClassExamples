[org 0x7c00]
mov ax, HELLO_MSG ; 1st variable
mov cx, WORLD_MSG ; 2nd variable 

mov bx, ax        ; pass argument via bx
call print_msg    ; call the function
mov bx, cx        ; pass argument via bx
call print_msg    ; call the function

mov bx, ax
call print_msg
mov bx, cx
call print_msg

jmp $

; we implement a function with interface
;     void print_msg(char* msg)
print_msg:
    pusha           ; push all registers to stack
    mov ah, 0x0e
LOOP:
    mov al, [bx]
    cmp al, 0
    je DONE_PRINT_MSG
    int 0x10
    inc bx
    jmp LOOP
DONE_PRINT_MSG:
    popa            ; pop all registers to stack
    ret

HELLO_MSG :
    db 'Hello!', 0 ;

WORLD_MSG :
    db 'World!', 0 ;

times 510-($-$$) db 0 
dw 0xaa55 

