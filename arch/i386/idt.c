/*   idt.c   */

#include <idt.h>
#include <isr.h>

__attribute__((aligned(0x10)))
idt_entry_t idt[256];           /* IDT */
static idtr_t idtr;             /* IDT pointer */

void idt_set_entry(uint8_t index, void (*isr)(regs_t), uint8_t flags) {
    idt[index] = (idt_entry_t) {
        .isr_low_addr = (uintptr_t) isr & 0xFFFF,
        .isr_high_addr = (uintptr_t) isr >> 16,
        .seg_selector = 0x8,
        .attributes = flags | 0x60,
        .all_zero = 0x00
    };
}

extern void idt_load();

void idt_init(void) {
    idtr.base = (uintptr_t) &idt[0];
    idtr.limit = sizeof(idt) - 1;
    isr_init();
    idt_load((uintptr_t) &idtr);
}
