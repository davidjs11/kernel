/*   ports.h   */

#ifndef PORTS_H
#define PORTS_H

static inline char inb(short port) {
    char r;
    __asm__ volatile ("inb %1, %0" : "=a" (r) : "dN" (port));
    return r;
}

static inline void outb(short port, char data) {
    __asm__ volatile ("outb %1, %0" : : "dN" (port), "a" (data));
}

static inline void io_wait(void) {
    outb(0x80, 0x00);
}

#endif // PORTS_H
