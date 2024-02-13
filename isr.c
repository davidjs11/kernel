/// isr.c ///////////////////////////////////////////////////////////

#include "utils.h"
#include "pic.h"
#include "idt.h"
#include "isr.h"
#include "vga.h"

extern void (*isr_stub_table[ISR_NUMBER])(regs_t);
isr_t handlers[ISR_NUMBER] = { 0 };

void isr_init() {
    for (uint8_t i=0; i<ISR_NUMBER; i++)
        idt_set_entry(i, isr_stub_table[i], 0x8E);

    for(uint8_t i=0; i<32; i++)
        isr_install(i, exception_handler);

    for(uint8_t i=32; i<48; i++)
        isr_install(i, irq_handler);
}

void isr_install(size_t i, isr_t handler) {
    handlers[i] = handler;
}

// called by common stub
void isr_handler(regs_t regs) {
    if (handlers[regs.int_no])
        vga_print("hello from isr!", regs.int_no & 0x0F);
}

// called by exceptions
void exception_handler(regs_t regs) {
    vga_print("KERNEL PANIC", VGA_COLOR_RED);
    HLT();
}

void irq_handler(regs_t regs) {
    vga_print("new irq", VGA_COLOR_RED);
    pic_end_of_interrupt(regs.int_no);
}
