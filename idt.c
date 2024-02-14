/// idt.c ///////////////////////////////////////////////////////////

#include "idt.h"
#include "gdt.h"
#include "isr.h"
#include "irq.h"
#include "vga.h"

// idt
__attribute__((aligned(0x10)))
static idt_entry_t idt[256];
extern void (*isr_stub_table[ISR_NUMBER])(regs_t regs);

// initialize idt
void idt_init() {
    // initialize 8259 pic (master at 0x20 and slave at 0x28)
    irq_init(0x20, 0x28);

    // setup idt register
    static idtr_t idtr;
    idtr.base = (uintptr_t) idt;
    idtr.limit = (uint16_t) sizeof(idt_entry_t)*IDT_MAX_DESCRIPTORS-1;

    // set entries
    for (size_t i=0; i<ISR_NUMBER; i++)
        idt_set_entry(i, isr_stub_table[i], 0x8E);

    isr_init();

    // load idt
    __asm__ volatile ("lidt (%0)" : : "r" (&idtr));
    __asm__ volatile ("sti");
}

// set an idt entry
void idt_set_entry(uint8_t index, void *isr, uint8_t flags) {
    idt[index] = (idt_entry_t) {
        .kernel_cs = GDT_OFFSET_CODE_SEGMENT,
        .attributes = flags,
        .reserved = 0,
        .isr_low  = (uint32_t) isr & 0xFFFF,
        .isr_high = (uint32_t) isr >> 16
    };
}
