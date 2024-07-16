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

    // get number of memory map entries
    int num = *((int *) 0x8000);
    printf("number of entries in system's memory map: ");
    putchar('0'+num);
    printf("\n");

    // infinite loooooooooooooop
    while(1);
}
