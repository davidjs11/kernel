/*   idt.c   */

#include "idt.h"
#include "vga.h"

void function_test(void) {
    char *buffer = (char *) VGA_ADDRESS;
    *buffer = 'X';
}
