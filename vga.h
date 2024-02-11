/// vga.h ///////////////////////////////////////////////////////////

#ifndef VGA_H
#define VGA_H


#define VGA_ADDRESS_SPACE       0xB8000
#define VGA_COLUMN_COUNT        80
#define VGA_ROW_COUNT           25
#define VGA_COLOR_BLACK         0x0
#define VGA_COLOR_BLUE          0x1
#define VGA_COLOR_GREEN         0x2
#define VGA_COLOR_CYAN          0x3
#define VGA_COLOR_RED           0x4
#define VGA_COLOR_MAGENTA       0x5
#define VGA_COLOR_BROWN         0x6
#define VGA_COLOR_WHITE         0x7
#define VGA_COLOR_GRAY          0x8
#define VGA_COLOR_LIGHT_BLUE    0x9
#define VGA_COLOR_LIGHT_GREEN   0xA
#define VGA_COLOR_LIGHT_CYAN    0xB
#define VGA_COLOR_LIGHT_RED     0xC
#define VGA_COLOR_LIGHT_MAGENTA 0xD
#define VGA_COLOR_YELLOW        0xE
#define VGA_COLOR_BRIGHT_WHITE  0xF

void vga_clear();
void print_vga(const char *str, const char color);

#endif // VGA_H
