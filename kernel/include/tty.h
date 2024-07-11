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

void tty_init(tty_t *);
size_t tty_get_rows(void);
size_t tty_get_cols(void);
void tty_set_cursor(tty_t *tty, size_t row, size_t col);
void tty_putchar(tty_t *, char c);
void tty_print(tty_t *, const char *src);
void tty_write(tty_t *, const char *src, size_t n);

#endif // KERNEL_TTY_H
