/// irq.c ///////////////////////////////////////////////////////////

#include "irq.h"
#include "pic.h"

// initialize irqs
void irq_init() {
    pic_init(0x20, 0x28);
}
