/// kernel.c ////////////////////////////////////////////////////////

#include "vga.h"
#include "idt.h"
#include "ports.h"

void wait();

void main() {
    idt_init();
    vga_clear();
    vga_print("kernel.c loaded successfully", VGA_COLOR_RED);
}
