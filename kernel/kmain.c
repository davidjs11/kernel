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

    printf("\nsearching for a free page frame...\n");
    void *mem = pmm_alloc();
    if (mem == NULL)
        printf("not found :-(\n");
    else printf("found at address 0x%08x !\n", mem);

    // infinite loooooooooooooop
    while(1);
}
