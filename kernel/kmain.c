/*   kmain.c   */

#include <tty.h>

void kmain(void) {
    // print something :-)
    tty_t tty;
    tty_init(&tty);
    tty_set_cursor(&tty, true);
    tty_set_color(&tty, TTY_RED, TTY_BLACK);
    tty_print(&tty, "welcome!");

    // test exceptions!! (when ready)
    // __asm__ volatile ("int $0x10");
    // tty_print(&tty, " bye!");

    while (1);  // infinite loooooooooooooop
}
