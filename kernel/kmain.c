/*   kmain.c   */

#include <init.h>
#include <tty.h>
#include <timer.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

extern tty_t tty;
void kmain(void) {
    tty_init();
    init_sys();
    timer_init(20); // start at 20 Hz

    // print something :-)
    printf("\nhello from kmain!\n\n");
    printf("printf test:\n");
    printf("%%:       %%\n", -1234567890);
    printf("int:     %d\n", -1234567890);
    printf("uint:    %u\n", -1234567890);
    printf("char:    %c\n", 'O');
    printf("string:  %s\n","welcome!!!!");

    // infinite loooooooooooooop
    while(1);
}
