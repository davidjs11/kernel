/// kernel.c ////////////////////////////////////////////////////////

#include "vga.h"
#include "idt.h"
#include "system.h"
#include "util.h"
#include "timer.h"
#include "string.h"

void main() {
    // init things
    idt_init();
    timer_init();

    // init vga
    vga_clear(VGA_BLACK);
    vga_print("kernel.c loaded", VGA_WHITE);

    // wait
    while(timer_get() < 1500);

    // a wild exception appeared
    int a = 10/0;
}
