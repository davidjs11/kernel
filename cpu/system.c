/// system.c ////////////////////////////////////////////////////////

#include "system.h"
#include "string.h"
#include "vga.h"

const char *panic_msg = "oh meu deus, panico do kernel!!!";
void panic(const char *err) {
    // print message
    vga_clear(VGA_BLUE);
    vga_print_at(panic_msg, VGA_TEXT_COLOR(VGA_BLUE, VGA_BRIGHT_WHITE),
                 VGA_ROWS/8, VGA_COLS/2-strlen(panic_msg)/2);
    vga_print_at(err, VGA_TEXT_COLOR(VGA_BRIGHT_WHITE, VGA_BLUE),
                 VGA_ROWS/5, VGA_COLS/2-strlen(err)/2);

    // here register values and more info should be printed
    // but guess who hasn't made an itoa function yet
    // heheheheh

    // halt the cpu
    HLT();
}
