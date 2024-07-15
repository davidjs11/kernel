/*   stdio.c   */

#include <stdio.h>
#include <tty.h>
#include <string.h>

extern tty_t tty; // global tty

int putchar(char c) {
    tty_putchar(&tty, c);
    return c;
}

// poor implementation for the moment
int printf(const char *format, ...) {
    int len = strlen(format);
    for (size_t i = 0; i < len; i++) {
        if (format[i] == '\n')
            tty_move_cursor(&tty, tty.row+1, 0);
        else
            tty_putchar(&tty, format[i]);
    }

    return len;
}
