/*   kmain.c   */

#include <tty.h>

void kmain(void) {
    // print something :-)
    tty_t tty;
    tty_init(&tty);
    size_t rows = tty_get_rows();
    size_t cols = tty_get_cols();
    tty_set_cursor(&tty, rows/2, cols/2-4);
    tty_print(&tty, "welcome!");

    while (1);  // infinite loooooooooooooop
}
