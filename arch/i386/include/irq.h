/*   irq.h   */

#ifndef I386_IRQ_H
#define I386_IRQ_H

#include <util.h>
#include <isr.h>

void irq_set_mask(uint8_t irq);
void irq_clear_mask(uint8_t irq);
void irq_install(uint8_t irq, isr_t isr);


#endif // I386_IRQ_H
