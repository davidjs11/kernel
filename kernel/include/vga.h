/*   vga.h   */

#ifndef VGA_H
#define VGA_H

#define VGA_ADDRESS 0xB8000

void vga_clear();
void vga_cursor_on();
void vga_cursor_off();
void vga_print(const char *str);

#endif // VGA_H
