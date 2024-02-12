#include "vga.h"

void isr_handler() {
    vga_print("hello from isr!", VGA_COLOR_RED);
    __asm__("hlt");
}
