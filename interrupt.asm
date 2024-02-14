; --- interrupt.asm -------------------------------------------------

; current interrupt mapping:
;   0x00 - 0x1F: cpu exceptions
;   0x20 - 0x2F: irqs

; stub defining macros
%macro isr_err_stub 1
[global isr_stub_%1]
isr_stub_%1:
    cli                 ; disable other interrupts
    push %1             ; push index
    jmp common_isr      ; call common handler
%endmacro

%macro isr_no_err_stub 1
[global isr_stub_%1]
isr_stub_%1:
    cli                 ; disable other interrupts
    push 33             ; push dummy error code
    push %1             ; push index
    jmp common_isr      ; call common handler
%endmacro


; common stubs
isr_no_err_stub 0       ; division by 0
isr_no_err_stub 1       ; debug
isr_no_err_stub 2       ; non maskable interrupt
isr_no_err_stub 3       ; breakpoint
isr_no_err_stub 4       ; into detected overflow
isr_no_err_stub 5       ; out of bounds
isr_no_err_stub 6       ; invalid opcode
isr_no_err_stub 7       ; no coprocessor
isr_err_stub    8       ; double fault
isr_no_err_stub 9       ; coprocessor segment overrun
isr_err_stub    10      ; bad tss
isr_err_stub    11      ; segment not present
isr_err_stub    12      ; stack fault
isr_err_stub    13      ; general protection fault
isr_err_stub    14      ; page fault
isr_no_err_stub 15      ; unknown interrupt
isr_no_err_stub 16      ; coprocessor fault
isr_err_stub    17      ; aligment check exception (486)
isr_no_err_stub 18      ; machine segment exception (pentium)
isr_no_err_stub 19      ; reserved
isr_no_err_stub 20      ; reserved
isr_no_err_stub 21      ; reserved
isr_no_err_stub 22      ; reserved
isr_no_err_stub 23      ; reserved
isr_no_err_stub 24      ; reserved
isr_no_err_stub 25      ; reserved
isr_no_err_stub 26      ; reserved
isr_no_err_stub 27      ; reserved
isr_no_err_stub 28      ; reserved
isr_no_err_stub 29      ; reserved
isr_no_err_stub 30      ; reserved
isr_no_err_stub 31      ; reserved
isr_no_err_stub 32      ; irq 0
isr_no_err_stub 33      ; irq 1
isr_no_err_stub 34      ; irq 2
isr_no_err_stub 35      ; irq 3
isr_no_err_stub 36      ; irq 4
isr_no_err_stub 37      ; irq 5
isr_no_err_stub 38      ; irq 6
isr_no_err_stub 39      ; irq 7
isr_no_err_stub 40      ; irq 8
isr_no_err_stub 41      ; irq 9
isr_no_err_stub 42      ; irq 10
isr_no_err_stub 43      ; irq 11
isr_no_err_stub 44      ; irq 12
isr_no_err_stub 45      ; irq 13
isr_no_err_stub 46      ; irq 14
isr_no_err_stub 47      ; irq 15


; common isr (used by stubs)
[extern isr_handler]
common_isr:
    ; save CPU state
    pusha           ; save all registers
    mov ax, ds      ; lower 16-bits of eax will be the data segment reg.
    push eax        ; save the data segment
    mov ax, 0x10    ; load kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; call C handler
    call isr_handler

    ; restore state
    pop eax         ; reload original data segment descriptor 
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa            ; reload original registers
    add esp, 8      ; clean pushed error code and ISR index
    sti             ; set interrupt flag
    iret            ; return from interrupt


; global stub table
global isr_stub_table
isr_stub_table:
%assign i 0             ; assign i=0
%rep    48              ; i<32
    dd isr_stub_%+i     ; declare isr_stub_i
%assign i i+1           ; i++
%endrep
