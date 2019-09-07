mov ax, 0x7c0
mov ds, ax
mov ax, HELLO_MSG ; 1st variable
mov cx, WORLD_MSG ; 2nd variable 

mov bx, ax        ; pass argument via bx and ds
call print_msg    ; call the function 
mov bx, cx        ; pass argument via bx and ds
call print_msg    ; call the function

mov bx, ax
call print_msg
mov bx, cx
call print_msg

jmp $

%include "print_msg.asm"

HELLO_MSG :
    db 'Hello!', 0 ;

WORLD_MSG :
    db 'World!', 0 ;

times 510-($-$$) db 0 
dw 0xaa55 

