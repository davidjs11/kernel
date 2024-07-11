/*   kmain.c   */

#include <tty.h>

void kmain(void) {
    // print something :-)
    tty_t tty;
    tty_init(&tty);
    tty_print(&tty, "welcome, ");

    // print something more colorful
    tty_set_color(&tty, TTY_LIGHT_RED, TTY_BLACK);
    tty_putchar(&tty, 'c');
    tty_set_color(&tty, TTY_LIGHT_CYAN, TTY_BLACK);
    tty_putchar(&tty, 'o');
    tty_set_color(&tty, TTY_LIGHT_MAGENTA, TTY_BLACK);
    tty_putchar(&tty, 'l');
    tty_set_color(&tty, TTY_LIGHT_GREEN, TTY_BLACK);
    tty_putchar(&tty, 'o');
    tty_set_color(&tty, TTY_LIGHT_BROWN, TTY_BLACK);
    tty_putchar(&tty, 'r');
    tty_set_color(&tty, TTY_LIGHT_BLUE, TTY_BLACK);
    tty_putchar(&tty, 's');
    tty_set_color(&tty, TTY_WHITE, TTY_BLACK);
    tty_putchar(&tty, '!');

    while (1);  // infinite loooooooooooooop
}
