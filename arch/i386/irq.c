/*   irq.c   */

#include <irq.h>
#include <ports.h>
#include <pic.h>

extern isr_t handlers[ISR_NUM];

void irq_set_mask(uint8_t irq) {
    // get mask
    uint8_t port = (irq < 8) ? PIC_MASTER_DATA : PIC_SLAVE_DATA;
    uint8_t mask = inb(port) | (1 << irq);
    outb(port, mask);
}

void irq_clear_mask(uint8_t irq) {
    // get mask
    uint8_t port = (irq < 8) ? PIC_MASTER_DATA : PIC_SLAVE_DATA;
    uint8_t mask = inb(port) & ~(1 << irq);
    outb(port, mask);
}

void irq_install(uint8_t irq, isr_t isr) {
    __asm__ volatile ("cli");
    handlers[irq+0x20] = isr;
    irq_clear_mask(irq);
    __asm__ volatile ("sti");
}
