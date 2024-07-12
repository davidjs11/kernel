/*   idt.h   */

#ifndef IDT_H
#define IDT_H

#include <util.h>

typedef struct {
    uint16_t    isr_low_addr;
    uint16_t    seg_selector;
    uint8_t     all_zero;
    uint8_t     attributes;
    uint16_t    isr_high_addr;
} __attribute__((packed)) idt_entry_t;

typedef struct {
    uint16_t limit;
    uintptr_t base;
} __attribute__((packed)) idtr_t;

void idt_set_entry(uint8_t index, void (*isr)(regs_t), uint8_t flags);
void idt_init(void);

#endif // IDT_H
