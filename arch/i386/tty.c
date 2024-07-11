/*   tty.c   */

/* TO-DO */
// - newline ??
// - tty switch

#include <ports.h>
#include <tty.h>
#include <vga.h>

// map colors to current implementation colors
tty_color_t colors[16] = {
    [TTY_BLACK]             = VGA_COLOR_BLACK,
    [TTY_BLUE]              = VGA_COLOR_BLUE,
    [TTY_GREEN]             = VGA_COLOR_GREEN,
    [TTY_CYAN]              = VGA_COLOR_CYAN,
    [TTY_RED]               = VGA_COLOR_RED,
    [TTY_MAGENTA]           = VGA_COLOR_MAGENTA,
    [TTY_BROWN]             = VGA_COLOR_BROWN,
    [TTY_LIGHT_GREY]        = VGA_COLOR_LIGHT_GREY,
    [TTY_DARK_GREY]         = VGA_COLOR_DARK_GREY,
    [TTY_LIGHT_BLUE]        = VGA_COLOR_LIGHT_BLUE,
    [TTY_LIGHT_GREEN]       = VGA_COLOR_LIGHT_GREEN,
    [TTY_LIGHT_CYAN]        = VGA_COLOR_LIGHT_CYAN,
    [TTY_LIGHT_RED]         = VGA_COLOR_LIGHT_RED,
    [TTY_LIGHT_MAGENTA]     = VGA_COLOR_LIGHT_MAGENTA,
    [TTY_LIGHT_BROWN]       = VGA_COLOR_LIGHT_BROWN,
    [TTY_WHITE]             = VGA_COLOR_WHITE
};

void tty_init(tty_t *tty) {
    // init tty struct
    tty->row = 0;
    tty->col = 0;
    tty->color = TTY_WHITE | TTY_BLACK << 4;
    tty->buffer = (char *) VGA_ADDRESS; // (for the moment)
    tty_move_cursor(tty, 0, 0);

    // clear vga screen
    char *buffer = (char *) VGA_ADDRESS;
    for (size_t i = 0; i < VGA_ROWS*VGA_COLS; i++) {
        *buffer = ' ';
        buffer += 2;
    }
}

size_t tty_get_rows(void) {
    return VGA_ROWS;
}

size_t tty_get_cols(void) {
    return VGA_COLS;
}

void tty_move_cursor(tty_t *tty, size_t row, size_t col) {
    // cursor position
    if (0 <= row && row < VGA_ROWS
    &&  0 <= col && col <= VGA_COLS) {
        tty->row = row;
        tty->col = col;

        uint16_t pos = row * VGA_COLS + col;

        outb(0x3D4, 0x0F);
        outb(0x3D5, (uint8_t) (pos & 0xFF));
        outb(0x3D4, 0x0E);
        outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
    }
}

void tty_set_cursor(tty_t *tty, bool state) {
    // * scanline for the moment will be _
    tty->cursor = state;
    if (state == true) {
        outb(0x3D4, 0x0A);
        outb(0x3D5, (inb(0x3D5) & 0xCF));
        outb(0x3D4, 0x0B);
        outb(0x3D5, (inb(0x3D5) & 0xEF));
    }
    else {
        outb(0x3D4, 0x0A);
        outb(0x3D5, 0x20);
    }
}

void tty_set_color(tty_t *tty, uint8_t front, uint8_t back) {
    tty->color = front | back << 4;
}

void tty_putchar(tty_t *tty, char c) {
    // print char
    char *buffer = &(tty->buffer[(tty->row*VGA_COLS+tty->col)*2]);
    *buffer++ = c;
    *buffer = tty->color;

    // increment cursor
    tty->col++;
    if (tty->col == VGA_COLS) {
        tty->col = 0;
        tty->row++;

        // if (tty->row == VGA_ROWS) // TODO
    }

    tty_move_cursor(tty, tty->row, tty->col);
}

void tty_print(tty_t *tty, const char *src) {
    while (*src) tty_putchar(tty, *src++);
}

void tty_write(tty_t *tty, const char *src, size_t n) {
    while (n--) tty_putchar(tty, *src++);
}
