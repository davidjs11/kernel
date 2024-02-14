/// pic.c ///////////////////////////////////////////////////////////

#include "irq.h"

// initialize pic (master and slave) for irqs
// 'offsetx' is vector offset for each pic's irq 
void irq_init(uint8_t offset1, uint8_t offset2) {
    // read mask registers
    uint8_t mask1 = inb(PIC1_DATA);
    uint8_t mask2 = inb(PIC2_DATA);

    // ICW1
    outb(PIC1_COMM, PIC_ICW1_INIT | PIC_ICW1_ICW4);
    outb(PIC2_COMM, PIC_ICW1_INIT | PIC_ICW1_ICW4);

    // ICW2 (offsets need to be multiple of 8 (0x08))
    outb(PIC1_DATA, offset1);
    outb(PIC2_DATA, offset2);

    // ICW3 (casquade mode)
    outb(PIC1_COMM, 1<<2); // master has slave at IRQ2 
    outb(PIC2_COMM, 0x02); // tell slave its casquade identity

    // ICW4
    outb(PIC1_COMM, PIC_ICW4_8086);
    outb(PIC2_COMM, PIC_ICW4_8086);

    // restore mask registers
    outb(PIC1_DATA, mask1);
    outb(PIC2_DATA, mask2);
}

// tell the pic that interrupt has been served
void irq_end_of_interrupt(uint8_t irq) {
    if (irq >= 8) outb(PIC2_COMM, PIC_EOI); // send to slave
    outb(PIC1_COMM, PIC_EOI);               // send to master
}

// disable pics
void irq_disable() {
    outb(PIC1_DATA, 0xFF);
    outb(PIC2_DATA, 0xFF);
}

// set interrupt mask register for an irq line
void irq_set_mask(uint8_t irq) {
    // detect pic (master or slave)
    uint16_t port = (irq < 8) ? PIC1_DATA : PIC2_DATA;

    // get and modify current interrupt mask 
    uint8_t mask = inb(port) | 1 << (irq & 7);

    // send new mask
    outb(port, mask);
}

// clear interrupt mask register for an irq line
void irq_clear_mask(uint8_t irq) {
    // detect pic (master or slave)
    uint16_t port = (irq < 8) ? PIC1_DATA : PIC2_DATA;

    // get and modify current interrupt mask 
    uint8_t mask = inb(port) & ~(1 << (irq & 7));

    // send new mask
    outb(port, mask);
}

// install interrupt handler given irq index
extern isr_t handlers[];
void irq_install(size_t i, isr_t handler) {
    handlers[i+0x20] = handler;
}
