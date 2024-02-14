/// timer.h /////////////////////////////////////////////////////////

#ifndef TIMER_H
#define TIMER_H

#include "util.h"

#define PIT_HZ      1193180
#define PIT_A       0x40
#define PIT_B       0x41
#define PIT_C       0x42
#define PIT_CONTROL 0x43
#define PIT_MASK    0xFF
#define PIT_SET     0x36
// #define PIT_CHOSEN_DIVISOR 1193180
#define PIT_CHOSEN_DIVISOR 363

// get current ticks from timer
uint32_t timer_get();

// set timer frequency
void timer_set(uint32_t hz);
void timer_init();
void timer_reset();
void timer_wait(uint32_t ticks);


#endif
