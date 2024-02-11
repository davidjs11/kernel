/// kernel.c ////////////////////////////////////////////////////////

#include "vga.h"
#include "idt.h"

void main() {
    idt_init();

    vga_clear();
    print_vga("kernel.c loaded successfully", VGA_COLOR_RED);
}
