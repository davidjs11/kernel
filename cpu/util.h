/// utils.h /////////////////////////////////////////////////////////

#ifndef UTIL_H
#define UTIL_H

#include <stddef.h>
#include <stdint.h>

/* CPU FUNCTIONS */
#define CLI(){__asm__("cli");}
#define STI(){__asm__("sti");}
#define HLT(){__asm__("hlt");}


/* IO FUNCTIONS */
// input a byte
static inline uint8_t inb(uint16_t port) {
    uint8_t res;
    __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
    return res;
}

// input two bytes word
static inline uint16_t inw(uint16_t port) {
    uint8_t res;
    __asm__("in %%dx, %%ax" : "=a" (res) : "d" (port));
    return res;
}

// output byte
static inline void outb(uint16_t port, uint8_t val) {
    __asm__("out %%al, %%dx" : : "a" (val), "d" (port));
}

// output two bytes word
static inline void outw(uint16_t port, uint16_t val) {
    __asm__("out %%ax, %%dx" : : "a" (val), "d" (port));
}

// io wait (currently unused)
static inline void io_wait(void) {
    outb(0x80, 0);
}

#endif // UTIL_H
