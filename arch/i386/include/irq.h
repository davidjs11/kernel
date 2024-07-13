/*   irq.h   */

#ifndef ARCH_IRQ_H
#define ARCH_IRQ_H

#include <util.h>
#include <isr.h>

void irq_set_mask(uint8_t irq);
void irq_clear_mask(uint8_t irq);
void irq_install(uint8_t irq, isr_t isr);


#endif // ARCH_IRQ_H
