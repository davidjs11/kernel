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

    printf("physical frame size: %uB\n", pmm_get_frame_size());
    printf("physical frames available: (%u/%u)\n",
           pmm_get_free_frames(), pmm_get_total_frames());

    // infinite loooooooooooooop
    while(1);
}
