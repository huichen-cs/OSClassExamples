; VGA
;   https://en.wikipedia.org/wiki/VGA-compatible_text_mode
;   https://en.wikipedia.org/wiki/Video_Graphics_Array#Color_palette

[org 0x7c00]
mov ax, 0xb800
mov es, ax

mov byte [es:0], 'H'
mov byte [es:1], 0x01

mov byte [es:2], 'e'
mov byte [es:3], 0x02

mov byte [es:4], 'l'
mov byte [es:5], 0x03

mov byte [es:6], 'l'
mov byte [es:7], 0x04

mov byte [es:8], 'o'
mov byte [es:9], 0x05

mov byte [es:10], ','
mov byte [es:11], 0x06

mov byte [es:12], 'W'
mov byte [es:13], 0x17

mov byte [es:14], 'o'
mov byte [es:15], 0x28

mov byte [es:16], 'r'
mov byte [es:17], 0x39

mov byte [es:18], 'l'
mov byte [es:19], 0x4a

mov byte [es:20], 'd'
mov byte [es:21], 0x5b

mov byte [es:22], '!'
mov byte [es:23], 0x6c

jmp $

times 510-($-$$) db 0
dw 0xaa55
