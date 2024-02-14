/// kernel.c ////////////////////////////////////////////////////////

#include "vga.h"
#include "idt.h"
#include "ports.h"
#include "timer.h"

void wait();

void main() {
    vga_clear();
    timer_init();
    idt_init();
    while(1) vga_print("interrupts working!", timer_get() & 0x05);
}
