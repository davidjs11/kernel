/*   tty.c   */

/* TO-DO */
// - colors!!
// - move vga cursor
// - tty switch

#include <tty.h>
#include <vga.h>


void tty_init(tty_t *tty) {
    // init tty struct
    tty->row = 0;
    tty->col = 0;
    tty->color = 0x00;
    tty->cursor = false;
    tty->buffer = (char *) VGA_ADDRESS; // (for the moment)

    // clear vga screen
    char *buffer = (char *) VGA_ADDRESS;
    for (size_t i = 0; i < VGA_ROWS*VGA_COLS; i++) {
        *buffer = ' ';
        buffer += 2;
    }
    vga_cursor_off();
}

size_t tty_get_rows(void) {
    return VGA_ROWS;
}

size_t tty_get_cols(void) {
    return VGA_COLS;
}

void tty_set_cursor(tty_t *tty, size_t row, size_t col) {
    if (0 <= row && row < VGA_ROWS
    && 0 <= col && col <= VGA_COLS) {
        tty->row = row;
        tty->col = col;
    }
}

void tty_putchar(tty_t *tty, char c) {
    // print char
    char *buffer = tty->buffer;
    buffer[(tty->row*VGA_COLS+tty->col)*2] = c;

    // increment cursor
    tty->col++;
    if (tty->col == VGA_COLS) {
        tty->col = 0;
        tty->row++;

        // if (tty->row == VGA_ROWS) // TODO
    }
}

void tty_print(tty_t *tty, const char *src) {
    while (*src) tty_putchar(tty, *src++);
}

void tty_write(tty_t *tty, const char *src, size_t n) {
    while (n--) tty_putchar(tty, *src++);
}
