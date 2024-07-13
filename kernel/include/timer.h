/*   timer.h   */

#ifndef KERNEL_TIMER_H
#define KERNEL_TIMER_H

#include <stdint.h>

void timer_init(uint32_t freq);
void timer_disable(void);
uint32_t timer_get(void);

#endif // KERNEL_TIMER_H
