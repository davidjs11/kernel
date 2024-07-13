/*   kmain.c   */

#include <init.h>
#include <tty.h>
#include <timer.h>

void kmain(void) {
    init_sys();

    // print something :-)
    tty_t tty;
    tty_init(&tty);
    tty_set_cursor(&tty, true);
    tty_set_color(&tty, TTY_RED, TTY_BLACK);
    tty_print(&tty, "welcome!");

    timer_init(20); // start at 20 Hz

    // wait for the timer for 1 sec
    while(1)
        if (timer_get() == 20) {
            tty_print(&tty, "nice!!");
            break;
        }

    while(1);   // infinite loooooooooooooop
}
