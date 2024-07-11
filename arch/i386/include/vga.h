/*   vga.h   */

/* TO-DO */
// - colors!!!!!!!!!!!

#ifndef VGA_H
#define VGA_H

#define VGA_ADDRESS 0xB8000
#define VGA_ROWS 25
#define VGA_COLS 80

void vga_cursor_on();       // maybe removed soon
void vga_cursor_off();

#endif // VGA_H
