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
    printf("\n-- printf() test --\n");
    printf("int:     %d\n", 1234567890);
    printf("uint:    %u\n", -1234567890);
    printf("hex:     0x%x\n", 0xDEADBEEF);
    printf("char:    %c\n", 'X');
    printf("string:  %s\n","welcome!!!");
    printf("\nhello from kmain! ");

    // infinite loooooooooooooop
    while(1);
}
