/*   kmain.c   */

#include <init.h>
#include <tty.h>
#include <timer.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <pmm.h>

extern uint32_t kernel_end;
void kmain(void) {
    tty_init();
    init_sys();
    timer_init(20); // start at 20 Hz

    // print something :-)
    printf("\nhello from kmain!\n");

    // request a lot of page frames
    printf("searching for %u free page frames:\n", 0x800);
    for (int i = 0; i < 0x800; i++) {
        char *mem = pmm_alloc();
        if (!mem) printf("%u: no free page found :-(\n", i);
        else printf("%u: new free page frame at 0x%08x !\n", i, mem);
    }

    // infinite loooooooooooooop
    while(1);
}
