/*   ports.h   */

#ifndef PORTS_H
#define PORTS_H

static inline char inb(short port) {
    char r;
    asm("inb %1, %0" : "=a" (r) : "dN" (port));
    return r;
}

static inline void outb(short port, char data) {
    asm("outb %1, %0" : : "dN" (port), "a" (data));
}

#endif // PORTS_H
