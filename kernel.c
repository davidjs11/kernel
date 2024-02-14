/// kernel.c ////////////////////////////////////////////////////////

#include "vga.h"
#include "idt.h"
#include "ports.h"

void wait();

void main() {
    vga_clear();
    idt_init();
}
