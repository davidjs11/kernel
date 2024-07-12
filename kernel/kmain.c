/*   kmain.c   */

#include <init.h>
#include <tty.h>

void kmain(void) {
    init_sys();

    // print something :-)
    tty_t tty;
    tty_init(&tty);
    tty_set_cursor(&tty, true);
    tty_set_color(&tty, TTY_RED, TTY_BLACK);
    tty_print(&tty, "welcome!");

    while(1);  // infinite loooooooooooooop
}
