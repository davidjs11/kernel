/// kernel.c ////////////////////////////////////////////////////////

#include "vga.h"
#include "idt.h"
#include "ports.h"

void main() {
    uint8_t res;
    res = inb(0x20);
    idt_init();

    vga_clear();
    print_vga("kernel.c loaded successfully", VGA_COLOR_RED);
}
