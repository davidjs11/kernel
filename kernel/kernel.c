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
    char buffer[256] = {0};
    vga_print(itoa(-14873, buffer, 10), VGA_WHITE);

    // wait
    while(timer_get() < 500);

    // a wild exception appeared
    __asm__("int $0x00");
}
