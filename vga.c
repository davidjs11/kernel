/// vga.c ///////////////////////////////////////////////////////////

#include "vga.h"

// clear vga text buffer
void vga_clear() {
    for(int i=0; i<VGA_COLUMN_COUNT*VGA_ROW_COUNT; i++)
        ((volatile char *)0xB8000)[2*i] = 0x00;
}

// print a string into the vga text buffer
void vga_print(const char *str, const char color) {
    volatile char *video = (volatile char *) 0xB8000;
    while(*str) {
        *video++ = *str++;
        *video++ = color;
    }
}
