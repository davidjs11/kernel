; --- interrupt.asm -------------------------------------------------
; isr 0-31  - cpu reserved
; irq 32-47 - interrupt handlers

; stub defining macros
%macro isr_err_stub 1
isr_stub_%+%1:
    push $0             ; push dummy error code
    push %1             ; push error code
    call common_isr     ; call common handler
    iret
%endmacro

%macro isr_no_err_stub 1
isr_stub_%+%1:
    push %1             ; push error code
    call common_isr     ; call common handler
    iret
%endmacro

; exceptions
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
isr_no_err_stub 17      ; aligment check exception (486)
isr_no_err_stub 18      ; machine segment exception (pentium)

; reserved exceptions
isr_no_err_stub 19
isr_no_err_stub 20
isr_no_err_stub 21
isr_no_err_stub 22
isr_no_err_stub 23
isr_no_err_stub 24
isr_no_err_stub 25
isr_no_err_stub 26
isr_no_err_stub 27
isr_no_err_stub 28
isr_no_err_stub 29
isr_no_err_stub 30
isr_no_err_stub 31

; interrupt requests
isr_no_err_stub 32
isr_no_err_stub 33
isr_no_err_stub 34
isr_no_err_stub 35
isr_no_err_stub 36
isr_no_err_stub 37
isr_no_err_stub 38
isr_no_err_stub 39
isr_no_err_stub 40
isr_no_err_stub 41
isr_no_err_stub 42
isr_no_err_stub 43
isr_no_err_stub 44
isr_no_err_stub 45
isr_no_err_stub 46
isr_no_err_stub 47

; stub table
global isr_stub_table
isr_stub_table:
%assign i 0             ; assign i=0
%rep    48              ; i<32
    dd isr_stub_%+i     ; declare isr_stub_i
%assign i i+1           ; i++
%endrep

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
