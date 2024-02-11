/// idt.c ///////////////////////////////////////////////////////////

#include "idt.h"
#include "gdt.h"

// idt
__attribute__((aligned(0x10)))
static idt_entry_t idt[256];
extern void* isr_stub_table[];

// initialize idt
void idt_init() {
    // setup idt register
    static idtr_t idtr;
    idtr.base = (uintptr_t) idt;
    idtr.limit = (uint16_t)sizeof(idt_entry_t)*IDT_MAX_DESCRIPTORS-1;

    // set entries
    for (uint8_t i=0; i<32; i++)
        idt_set_entry(i, isr_stub_table[i], 0x8E);

    // load idt
    __asm__ volatile ("lidt (%0)" : : "r" (&idtr));
    __asm__ volatile ("sti");
}

// set an idt entry
void idt_set_entry(uint8_t index, void *isr, uint8_t flags) {
    // get the entry from the idt
    idt_entry_t *entry = &idt[index];

    // set entry values
    entry->kernel_cs = GDT_OFFSET_CODE_SEGMENT; /* code seg offset */
    entry->attributes = flags;                  /* flags */
    entry->reserved = 0;                        /* all 0 */
    entry->isr_low  = (uint32_t) isr & 0xFFFF;  /* isr address low */
    entry->isr_high = (uint32_t) isr >> 16;     /* isr address high */
}


// temporal exception handler
void tmp_exception_handler() {
    __asm__ volatile ("cli;hlt");
}
