/// kernel.c ////////////////////////////////////////////////////////

#include "vga.h"
#include "idt.h"
#include "util.h"
#include "timer.h"

void wait();

void main() {
    vga_clear();
    idt_init();
    timer_init();
    vga_print("kernel.c loaded!!!", VGA_COLOR_RED);
    HLT();
}
