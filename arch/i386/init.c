/*   init.c   */

#include <init.h>
#include <util.h>
#include <tty.h>
#include <idt.h>
#include <isr.h>
#include <pic.h>
#include <irq.h>

void init_sys(void) {
    pic_remap(0x20, 0x28);
    isr_init();
    idt_init();
}
