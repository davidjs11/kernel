/// ports.h /////////////////////////////////////////////////////////

#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>


/* INPUT */
static inline uint8_t inb(uint16_t port) {
    uint8_t res;
    __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
    return res;
}

static inline uint16_t inw(uint16_t port) {
    uint8_t res;
    __asm__("in %%dx, %%ax" : "=a" (res) : "d" (port));
    return res;
}


/* OUTPUT */
static inline void outb(uint16_t port, uint8_t val) {
    __asm__("out %%al, %%dx" : : "a" (val), "d" (port));
}

static inline void outw(uint16_t port, uint16_t val) {
    __asm__("out %%ax, %%dx" : : "a" (val), "d" (port));
}


/* IO WAIT */
static inline void io_wait(void) {
    outb(0x80, 0);
}

#endif // PORTS_H
