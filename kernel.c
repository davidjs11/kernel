/// kernel.c ////////////////////////////////////////////////////////

#include "vga.h"
#include "idt.h"
#include "util.h"
#include "timer.h"

void wait();

char buffer[VGA_ROW_COUNT*VGA_COLUMN_COUNT];
void main() {
    for(size_t i=0; i<sizeof(buffer); i++) buffer[i] = 'ñ';
    vga_clear();
    idt_init();
    timer_init();
    while(timer_get() < 255) vga_print(buffer, timer_get() & 0xFF);
    vga_print("adiooooo", VGA_COLOR_RED);
    HLT();
}
