[org 0x7c00]

; Specifies the code is written for 16bits architecture
; and the code should be run in 16bits environment (all register will be 16bits wide)
[bits 16]

section code

.switch:

    mov ax, 0x4f01 ; vbe
    mov cx, 0x117
    mov bx, 0x0800
    mov es, bx
    mov di, 0x00
    int 0x10 

    mov ax, 0x4f02
    mov bx, 0x117
    int 0x10

    xor ax, ax
    mov ds, ax
    mov es, ax

    mov bx, 0x1000
    mov ah, 0x02
    mov al, 1
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02
    int 0x13
 
    cli
    lgdt [gdt_descriptor]

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax

    jmp code_seg:protected_start


[bits 32]
protected_start:
    mov ax, data_seg
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    mov ebp, 0x90000
    mov esp, ebp

    call 0x1000
    
    jmp $

gdt_begin:
gdt_null_descriptor:
    dd 0x00
    dd 0x00
gdt_code_seg:
    dw 0xffff
    dw 0x00
    db 0x00
    db 10011010b
    db 11001111b
    db 0x00
gdt_data_seg:
    dw 0xffff
    dw 0x00
    db 0x00
    db 10010010b
    db 11001111b
    db 0x00
gdt_end:
gdt_descriptor:
    dw gdt_end - gdt_begin - 1
    dd gdt_begin

code_seg equ gdt_code_seg - gdt_begin
data_seg equ gdt_data_seg - gdt_begin

times 510 - ($ - $$) db 0x00

db 0x55
db 0xaa