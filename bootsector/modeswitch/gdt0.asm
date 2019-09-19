; See https://wiki.osdev.org/Global_Descriptor_Table
;     and
;     https://www.intel.com/content/www/us/en/architecture-and-technology/64-ia-32-architectures-software-developer-vol-3a-part-1-manual.html
; a simple flat Global Descriptor Table (GDT)
gdt:

.sd_null: ; 8 bytes
    db 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

.sd_code: ; 8 bytes
    db 0xff, 0xff ; bits 0 - 15 of segment limit of 20 bits
    db 0x00, 0x00   ; bits  0 - 15 of segment base of 32 bits
    db 0x00         ; bits 16 - 23 of segment base of 32 bits
    ; Bits
    ;   P    = 1    -> segemnt present (1 for present in memory; 0 for not)
    ;   DPL  = 00   -> privilege level 00 for highest  (11 for lowest)
    ;   S    = 1    -> 0 for system; 1 for code or data
    ;   Type = 1010 -> segment type 4 bits as follows
    ;                  code: 
    ;                       1 for code (0 for data)
    ;                  conforming: 
    ;                       If 1 code in this segment can be executed from 
    ;                           an equal or lower privilege level. 
    ;                           For example, code in ring 3 can far-jump to 
    ;                           conforming code in a ring 2 segment.  The 
    ;                           privl-bits represent the highest privilege 
    ;                           level that is allowed to execute the segment.
    ;                           For example, code in ring 0 cannot far-jump 
    ;                           to a conforming code segment with privl==0x2, 
    ;                           while code in ring 2 and 3 can. Note that the 
    ;                           privilege level remains the same, ie. a 
    ;                           far-jump form ring 3 to a privl==2-segment 
    ;                           remains in ring 3 after the jump.
    ;                       If 0 code in this segment can only be executed 
    ;                           from the ring set in privl. 
    ;                  readable: 1 for readable, 0 for execute-only
    ;                  accessed: 0 initially, if accessed, CPU sets it to 1
    db 0b10011010 ; 1st flags , type flags
    ; Bits
    ;   G    = 1 -> offset is in unit 4K (2^12 bytes)
    ;   D/B  = 1 -> 1 for 32-bit segment; 0 for 16-bit
    ;   L    = 0 -> 64-bit code segment? 0 for not, ununsed on 32-bit processor
    ;   AVL  = 0 -> Not available to system programmers
    ;   Segment Limit (bits 19:16) = 1111
    db 0b11001111 ; 2nd flags , Limit ( bits 16 -19)
    db 0x00 ; bits 24 - 31 of segment base of 32bits

.sd_data: ; 8 bytes
    db 0xff, 0xff ; bits 0 - 15 of segment limit of 20 bits
    db 0x00, 0x00   ; bits  0 - 15 of segment base of 32 bits
    db 0x00         ; bits 16 - 23 of segment base of 32 bits
    ; Bits
    ;   P    = 1    -> segemnt present (1 for present in memory; 0 for not)
    ;   DPL  = 00   -> privilege level 00 for highest  (11 for lowest)
    ;   S    = 1    -> 0 for system; 1 for code or data
    ;   Type = 0010 -> segment type 4 bits as follows
    ;                  code: 
    ;                       0 for data (1 for code)
    ;                  conforming: 
    ;                       If 1 code in this segment can be executed from 
    ;                           an equal or lower privilege level. 
    ;                           For example, code in ring 3 can far-jump to 
    ;                           conforming code in a ring 2 segment.  The 
    ;                           privl-bits represent the highest privilege 
    ;                           level that is allowed to execute the segment.
    ;                           For example, code in ring 0 cannot far-jump 
    ;                           to a conforming code segment with privl==0x2, 
    ;                           while code in ring 2 and 3 can. Note that the 
    ;                           privilege level remains the same, ie. a 
    ;                           far-jump form ring 3 to a privl==2-segment 
    ;                           remains in ring 3 after the jump.
    ;                       If 0 code in this segment can only be executed 
    ;                           from the ring set in privl. 
    ;                  readable: 1 for readable, 0 for execute-only
    ;                  accessed: 0 initially, if accessed, CPU sets it to 1
    db 0b10010010   ; 
    ; Bits
    ;   G    = 1 -> offset is in unit 4K (2^12 bytes)
    ;   D/B  = 1 -> 1 for 32-bit segment; 0 for 16-bit
    ;   L    = 0 -> 64-bit code segment? 0 for not, ununsed on 32-bit processor
    ;   AVL  = 0 -> Not available to system programmers
    ;   Segment Limit (bits 19:16) = 1111
    db 0b11001111   ; 
    db 0x00         ; base (bits 24 - 31)

.gdt_end:


GDT_DESCRIPTOR: ; to be loaded by instruction lgdt
    ; The size is the size of the table subtracted by 1. This is because the
    ; maximum value of size is 65535, while the GDT can be up to 65536 bytes (a
    ; maximum of 8192 entries). Further no GDT can have a size of 0. 
    dw gdt.gdt_end - gdt - 1    
    ; The offset is the linear address of the table itself
    dd gdt
    

CODE_SEG equ gdt.sd_code - gdt
DATA_SEG equ gdt.sd_data - gdt
