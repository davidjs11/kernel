/*   kmain.c   */

#include <init.h>
#include <tty.h>
#include <timer.h>
#include <string.h>
#include <stdlib.h>

void kmain(void) {
    init_sys();
    timer_init(20); // start at 20 Hz

    // print something :-)
    tty_t tty;
    tty_init(&tty);
    tty_set_cursor(&tty, true);
    tty_set_color(&tty, TTY_RED, TTY_BLACK);

    // print 5 whitespaces in the most convoluted way
    for (int i = 0; i < (-1*atoi("-5")); i++)
        tty_putchar(&tty, ' ');
    tty_print(&tty, "welcome!");

    // abort after 2 seconds
    while(1) if (timer_get() == 40) abort();

    // infinite loooooooooooooop
    while(1);
}
