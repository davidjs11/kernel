/// idt.c ///////////////////////////////////////////////////////////

#include "idt.h"
#include "gdt.h"
#include "pic.h"
#include "vga.h"

// idt
__attribute__((aligned(0x10)))
static idt_entry_t idt[256];
extern void* isr_stub_table[];

// initialize idt
void idt_init() {
    // initialize 8259 pic
    pic_init(0x20, 0x28);

    // setup idt register
    static idtr_t idtr;
    idtr.base = (uintptr_t) idt;
    idtr.limit = (uint16_t) sizeof(idt_entry_t)*IDT_MAX_DESCRIPTORS-1;

    // set entries
    for (uint8_t i=0; i<48; i++)
        idt_set_entry(i, isr_stub_table[i], 0x8E);

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
