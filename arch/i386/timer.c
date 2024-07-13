/*   timer.c   */

#include <timer.h>
#include <ports.h>
#include <util.h>
#include <pit.h>
#include <isr.h>
#include <irq.h>

uint64_t ticks;

void timer_handler(regs_t *regs) {
    ticks++;
}

void timer_init(uint32_t freq) {
    if (!freq) return;

    irq_install(0x00, timer_handler);
    uint16_t divisor = PIT_CLK_HZ / freq;

    // send command word and frequency divisor
    outb(PIT_OCW, 0x36);    // mode 3 (square wave generator); counter 0
    outb(PIT_CLK_1, divisor & 0xFF);
    outb(PIT_CLK_1, (divisor >> 8) & 0xFF);

    ticks = 0;
}

uint64_t timer_get(void) {
    return ticks;
}


void timer_disable(void) {
    /* TO-DO */
}
