/*   entry.S   */
.code32

/* kernel entry point */
.global _start
_start:
    jmp kmain
    jmp .

.section .text
.align 4

/* idt-loader */
.global idt_load
.type idt_load, @function
idt_load:
    mov 4(%esp), %eax
    lidt (%eax)
    sti
    ret

/* exception stubs */
.macro isr_no_err index
    .global isr_\index
    isr_\index:
        cli
        push $0
        push $\index
        jmp isr_common
.endm

.macro isr_err index
    .global isr_\index
    isr_\index:
        cli
        push $\index
        jmp isr_common
.endm

/* define stubs */
isr_no_err  0
isr_no_err  1
isr_no_err  2
isr_no_err  3
isr_no_err  4
isr_no_err  5
isr_no_err  6
isr_no_err  7
isr_err     8
isr_no_err  9
isr_err     10
isr_err     11
isr_err     12
isr_err     13
isr_err     14
isr_no_err  15
isr_no_err  16
isr_no_err  17
isr_no_err  18
isr_no_err  19
isr_no_err  20
isr_no_err  21
isr_no_err  22
isr_no_err  23
isr_no_err  24
isr_no_err  25
isr_no_err  26
isr_no_err  27
isr_no_err  28
isr_no_err  29
isr_no_err  30
isr_no_err  31
isr_no_err  32
isr_no_err  33
isr_no_err  34
isr_no_err  35
isr_no_err  36
isr_no_err  37
isr_no_err  38
isr_no_err  39
isr_no_err  40
isr_no_err  41
isr_no_err  42
isr_no_err  43
isr_no_err  44
isr_no_err  45
isr_no_err  46
isr_no_err  47

/* define common handler */
.extern isr_handler
.type isr_handler, @function

isr_common:
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    cld

    call isr_handler

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $0x8, %esp

    iret
