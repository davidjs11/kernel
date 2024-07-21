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

    // check if kernel has been allocated
    printf("is kernel page frame free?...\n");
    for (int i = 0; i < 0x12; i++) {
        char *mem = pmm_alloc();
        printf("%02u: new free page frame at 0x%08x !\n", i, mem);

        // in case that the kernel page frame is available
        if (mem == (char *) 0x10000) {
            printf("kernel page was free :-(\n");
            while(1);
        }
    }
    printf("kernel has been allocated correctly!! :-)\n");

    // infinite loooooooooooooop
    while(1);
}
