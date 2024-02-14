/// irq.h ///////////////////////////////////////////////////////////

#ifndef IRQ_H
#define IRQ_H

#include <stdint.h>
#include "ports.h"
#include "isr.h"

/* MACROS */
// ports   
#define PIC1        0x20        /* io address for master pic */
#define PIC2        0xA0        /* io address for slave pic */
#define PIC1_COMM   PIC1        /* command address */
#define PIC2_COMM   PIC2
#define PIC1_DATA   (PIC1+1)    /* data address */
#define PIC2_DATA   (PIC2+1)

// commands / initialization command words (ICW)
#define PIC_EOI         0x20    /* end of interrupt code */
#define PIC_ICW1_INIT	0x10	/* init pic (0x10) */
#define PIC_ICW1_ICW4   0x01    /* tell pic there'll be icw4 */
#define PIC_ICW4_8086   0x01    /* 8086 mode */

/* FUNCTIONS */
// initialize pics (master and slave) for irqs
void irq_init(uint8_t offset1, uint8_t offset2);

// tell the irq that interrupt has been served
void irq_end_of_interrupt(uint8_t irq);

// disable irqs
void irq_disable();

// set interrupt mask register bit for an irq line
void irq_set_mask(uint8_t irq);

// clear interrupt mask register bit for an irq line
void irq_clear_mask(uint8_t irq);

// TODO
void irq_install(size_t i, isr_t handler);


#endif // IRQ_H
