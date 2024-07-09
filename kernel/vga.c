/*   vga.c   */

#include <vga.h>
#include <ports.h>

void vga_clear() {
    char *buffer = (char *) VGA_ADDRESS;
    for (short i = 0; i < 80*25; i++) {
        *buffer = ' ';
        buffer += 2;
    }
}

void vga_cursor_on() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0));
    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0));
}

void vga_cursor_off() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void vga_print(const char *str) {
    char *buffer = (char *) VGA_ADDRESS;
    while (*str) {
        *buffer++ = *str++;
        buffer++;
    }
}
