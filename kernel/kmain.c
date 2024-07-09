/*   kmain.c   */

#include <vga.h>
#include <ports.h>

void kmain(void) {
    // print something
    vga_clear();
    vga_cursor_off();
    vga_print("printing test.");

    while (1);  // infinite looooooooooop
}
