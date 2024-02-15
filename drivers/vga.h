/// vga.h ///////////////////////////////////////////////////////////

#ifndef VGA_H
#define VGA_H

#include "util.h"

/* MACROS */
#define VGA_ADDRESS_SPACE       0xB8000
#define VGA_COLS                80
#define VGA_ROWS                25
#define VGA_BLACK               0x0
#define VGA_BLUE                0x1
#define VGA_GREEN               0x2
#define VGA_CYAN                0x3
#define VGA_RED                 0x4
#define VGA_MAGENTA             0x5
#define VGA_BROWN               0x6
#define VGA_WHITE               0x7
#define VGA_GRAY                0x8
#define VGA_LIGHT_BLUE          0x9
#define VGA_LIGHT_GREEN         0xA
#define VGA_LIGHT_CYAN          0xB
#define VGA_LIGHT_RED           0xC
#define VGA_LIGHT_MAGENTA       0xD
#define VGA_YELLOW              0xE
#define VGA_BRIGHT_WHITE        0xF
#define VGA_TEXT_COLOR(_t,_b)   (_t)|(_b<<4)


/* FUNCTIONS */
// clear the screen with a color
void vga_clear(uint8_t color);

// print text in the screen
void vga_print(const char *str, uint8_t color);

// print text at a given position
void vga_print_at(const char *str, uint8_t color, uint8_t i, uint8_t j);

#endif // VGA_H
