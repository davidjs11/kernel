/// pic.h ///////////////////////////////////////////////////////////

#ifndef PIC_H
#define PIC_H

#include <stdint.h>
#include "ports.h"

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
// initialize pics (master and slave)
void pic_init(uint8_t offset1, uint8_t offset2);

// tell the pic that interrupt has been served
void pic_end_of_interrupt(uint8_t irq);

// disable pics
void pic_disable();

// set interrupt mask register bit for an irq line
void pic_set_mask(uint8_t irq);

// clear interrupt mask register bit for an irq line
void pic_clear_mask(uint8_t irq);


#endif // PIC_H
