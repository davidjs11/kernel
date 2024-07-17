/*   init.c   */

#include <init.h>
#include <util.h>
#include <tty.h>
#include <idt.h>
#include <isr.h>
#include <pic.h>
#include <irq.h>
#include <stdio.h>

void init_sys(void) {
    /* interrupts */
    printf("- remapping PIC...  ");
    pic_remap(0x20, 0x28);
    printf("OK\n");
    printf("- loading ISR...    ");
    isr_init();
    printf("OK\n");
    printf("- setting up IDT... ");
    idt_init();
    printf("OK\n");

    /* memory map */
    int num = *((int *) 0x8000);
    printf("number of entries in system's memory map: ");
    putchar('0'+num);
    printf("\n");
}
