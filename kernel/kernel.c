/// kernel.c ////////////////////////////////////////////////////////

#include "vga.h"
#include "idt.h"
#include "system.h"
#include "util.h"
#include "timer.h"

void main() {
    idt_init();
    timer_init();

    vga_clear(VGA_BLACK);
    vga_print("kernel.c loaded", VGA_WHITE);
              

    while(timer_get() < 1000);

    vga_clear(VGA_BLUE);
    vga_print_at("kernel panic",
                VGA_TEXT_COLOR(VGA_BLUE, VGA_BRIGHT_WHITE),
                 VGA_ROWS/8, VGA_COLS/2-6);
    // panic();
}
