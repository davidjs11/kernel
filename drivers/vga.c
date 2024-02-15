/// vga.c ///////////////////////////////////////////////////////////

#include "vga.h"

// clear vga text buffer
void vga_clear(uint8_t color) {
    for(int i=0; i<VGA_COLS*VGA_ROWS; i++) {
        ((volatile char *)0xB8000)[2*i] = 0x00;
        ((volatile char *)0xB8000)[2*i+1] = color << 4;
    }
}

// print a string into the vga text buffer
void vga_print(const char *str, uint8_t color) {
    volatile char *video = (volatile char *) 0xB8000;
    while(*str) {
        *video++ = *str++;
        *video++ |= color;
    }
}

// print a string at a given position
void vga_print_at(const char *str, uint8_t color, uint8_t i, uint8_t j) {
    char *video = (char *) 0xB8000 + 2*(j+i*VGA_COLS);

    while(*str) {
        *video++ = *str++;
        *video++ |= color;
    }
}
