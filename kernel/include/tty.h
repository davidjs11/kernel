/*   tty.h   */

#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    size_t  row;
    size_t  col;
    uint8_t color;
    bool    cursor;
    char*   buffer;
} tty_t;

// currently based on vga colors -> may change in the future
typedef enum {
    TTY_BLACK,
    TTY_BLUE,
    TTY_GREEN,
    TTY_CYAN,
    TTY_RED,
    TTY_MAGENTA,
    TTY_BROWN,
    TTY_LIGHT_GREY,
    TTY_DARK_GREY,
    TTY_LIGHT_BLUE,
    TTY_LIGHT_GREEN,
    TTY_LIGHT_CYAN,
    TTY_LIGHT_RED,
    TTY_LIGHT_MAGENTA,
    TTY_LIGHT_BROWN,
    TTY_WHITE
} tty_color_t;

void tty_init(tty_t *);
size_t tty_get_rows(void);
size_t tty_get_cols(void);
void tty_set_cursor(tty_t *, size_t row, size_t col);
void tty_set_color(tty_t *, uint8_t front, uint8_t back);
void tty_putchar(tty_t *, char c);
void tty_print(tty_t *, const char *src);
void tty_write(tty_t *, const char *src, size_t n);

#endif // KERNEL_TTY_H
