[org 0x1000]
[bits 32]

jmp print
times 210 db 0x66
print:
    mov edx, 0xB8000    ; get VGA memory address

print_loop:
    ; set character
    mov al, [ebx]   ; get character from buffer
    mov ah, 0x0F    ; (white on black)

    cmp al, 0x0     ; check if null-char has been reached
    je print_vga_end

    mov [edx], ax   ; set character value into VGA memory
    add edx, 2      ; increment VGA buffer pointer
    add ebx, 1      ; increment buffer pointer

    jmp print_loop  ; return to loop 

print_vga_end:
    jmp $
