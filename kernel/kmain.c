/*   kmain.c   */

#include <init.h>
#include <tty.h>
#include <timer.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern tty_t tty;
void kmain(void) {
    init_sys();
    timer_init(20); // start at 20 Hz
    tty_init();

    // print something :-)
    printf("hello from kmain!\n");

    // abort after 3 seconds
    while(1) if (timer_get() == 60) abort();

    // infinite loooooooooooooop
    while(1);
}
