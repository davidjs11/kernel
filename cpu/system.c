/// system.c ////////////////////////////////////////////////////////

#include "system.h"
#include "vga.h"

void panic(const char *err) {
    // print message
    vga_clear(VGA_BLUE);
    vga_print_at("kernel panic",
                VGA_TEXT_COLOR(VGA_BLUE, VGA_BRIGHT_WHITE),
                 VGA_ROWS/8, VGA_COLS/2-6);
    vga_print_at((char*) err,
                 VGA_TEXT_COLOR(VGA_BRIGHT_WHITE, VGA_BLUE),
                 VGA_ROWS/5, VGA_COLS/2/*-strlen(err)/2*/-7);

    // here register values and info should be printed
    // but guess who hasn't made an itoa function yet
    // heheheheh

    // halt the cpu
    HLT();
}
