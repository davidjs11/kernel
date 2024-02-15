/// isr.c ///////////////////////////////////////////////////////////

#include "util.h"
#include "irq.h"
#include "idt.h"
#include "isr.h"
#include "vga.h"
#include "system.h"

isr_t handlers[ISR_NUMBER];
extern isr_t isr_stub_table[];

const char *exception_text[32] = {
    "DIVISION BY 0",
    "DEBUG",
    "NON MASKABLE INTERRUPT",
    "BREAKPOINT",
    "INTO DETECTED OVERFLOW",
    "OUT OF BOUNDS",
    "INVALID OPCODE",
    "NO COPROCESSOR",
    "DOUBLE FAULT",
    "COPROCESSOR SEGMENT OVERRUN",
    "BAD TSS",
    "SEGMENT NOT PRESENT",
    "STACK FAULT",
    "GENERAL PROTECTION FAULT",
    "PAGE FAULT",
    "UNKNOWN INTERRUPT",
    "COPROCESSOR FAULT",
    "ALIGMENT CHECK EXCEPTION (486)",
    "MACHINE SEGMENT EXCEPTION (PENTIUM)",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED",
    "RESERVED"
};

// initialize isr stub and handler arrays
void isr_init() {
    // initialize idt entries pointing to stubs
    for(size_t i=0; i<ISR_NUMBER; i++)
        idt_set_entry(i, isr_stub_table[i], 0x8E);

    // install exception handlers
    for(size_t i=0; i<32; i++) isr_install(i, exception_handler);
}

// handle an interrupt request
void isr_handler(regs_t regs) {
    // call handler function (if available)
    if (handlers[regs.int_no]) handlers[regs.int_no](regs);

    // if it's an irq (isr from 0x20 to 0x2F), send EOI
    if (0x20 <= regs.int_no && regs.int_no <= 0x2F)
        irq_end_of_interrupt(regs.int_no-0x20);
}

// install interrupt handler
void isr_install(size_t i, isr_t handler) {
    handlers[i] = handler;
}

// TEMPORAL
// exception handler
void exception_handler(regs_t regs) {
    panic(exception_text[regs.int_no]);
}
