/*   kmain.c   */

#include "vga.h"
#include "ports.h"
#include "idt.h"

void kmain(void) {
    // print something
    vga_clear();
    vga_cursor_off();
    vga_print("  - it works!!!");
    function_test(); // this should print an 'X' at the beginning

    while (1);  // infinite looooooooooop
}
