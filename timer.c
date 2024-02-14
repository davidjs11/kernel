/// timer.c /////////////////////////////////////////////////////////

#include "timer.h"
#include "isr.h"
#include "irq.h"


// timer state struct
static struct {
    uint32_t freq;
    uint64_t ticks;
} state;

// timer interrupt handler
void timer_handler(regs_t regs) {
    state.ticks++;
}

// set timer for specific frequency
void timer_set(uint32_t hz) {
    // timer set command
    outb(PIT_CONTROL, PIT_SET);

    // send desired frequency
    uint16_t divisor = (uint16_t) (1193131.666 / hz);
    outb(PIT_A, divisor & PIT_MASK);
    outb(PIT_A, (divisor>>8) & PIT_MASK);
}

// initialize timer
void timer_init() {
    // init state
    state.freq = PIT_CHOSEN_DIVISOR;
    state.ticks = 0;
    timer_set(PIT_CHOSEN_DIVISOR);

    // install timer handler
    irq_install(0, timer_handler);
}

// get current ticks from the timer
uint32_t timer_get() {
    return state.ticks;
};

// reset ticks
void timer_reset() {
    state.ticks = 0;
}
