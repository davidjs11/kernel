; --- boot_sector.asm -----------------------------------------------

[org 0x7C00]

KERNEL_OFFSET equ 0x1000

[bits 16]
start:
    ; setup stack
    mov bp, 0x9000
    mov sp, bp

    ; read disk
    mov bx, KERNEL_OFFSET
    mov dh, 0x09
    call read_disk

    ; disable cursor
    xor ah, ah
    inc ah
    mov ch, 0x3F
    int 0x10

    ; switch to 32 bits
    call switch_protected_mode


[bits 32]
start_32:
    ; set segment registers
    mov ax, GDT_32.data
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; set stack
    mov ebp, 0x90000
    mov esp, ebp

    ; print something
    call KERNEL_OFFSET


; disk reading routine
; 'bx' buffer address
; 'dh' number of sectors to read
; 'dl' drive index
[bits 16]
read_disk:
    ; save registers
    pusha
    push dx         ; save number of sectors to read

    ; disk reading interrupt
    mov ah, 0x02    ; 'read' function
    mov al, dh      ; number of sectors to read
    mov cl, 02      ; sector index
    xor ch, ch      ; track index
    xor dh, dh      ; head index
    int 0x13        ; BIOS disk interrupt
    
    ; error checking
    jc read_disk    ; if error -> try again
    pop dx          ; recover number of sectors to read
    cmp al, dh      ; check if every sector was read
    jne read_disk   ; if not -> try again

    ; recover registers
    popa
    ret


; switch to 32 bit protected mode
[bits 16]
switch_protected_mode:
    cli                     ; disable interrupts
    lgdt [GDT_32.pointer]   ; load GDT descriptor/pointer

    ; set 32-bit flag on control register
    mov eax, cr0
    or  eax, 0x1
    mov cr0, eax

    ; far jump to 32 bit mode
    jmp GDT_32.code:start_32
    

; gdt
GDT_32:
    ; null segment
    .null: equ $ - GDT_32
        dd 0x00000000
        dd 0x00000000

    ; base: 0x0 - limit: 0xFFFF
    .code: equ $ - GDT_32
        dq 0x00CF9A000000FFFF

    ; base: 0x00 - limit: 0xFFFF
    .data: equ $ - GDT_32
        dq 0x00CF92000000FFFF

    ; descriptor (pointer to gdt)
    .pointer:
        dw $ - GDT_32 - 1   ; limit
        dd GDT_32           ; base

    ; (0x00) -> NULL
    ; (0x08) -> CODE
    ; (0x10) -> DATA

; mbr signature
times 510-($-$$) db 0x00
dw 0xAA55
