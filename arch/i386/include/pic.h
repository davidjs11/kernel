/*   pic.h   */

#ifndef I386_PIC_H
#define I386_PIC_H

#include <util.h>

#define PIC_MASTER_COMMAND  0x20
#define PIC_MASTER_DATA     0x21
#define PIC_SLAVE_COMMAND   0xA0
#define PIC_SLAVE_DATA      0xA1

#define ICW1_ICW4	        0x01
#define ICW1_INIT	        0x10
#define ICW4_8086	        0x01

void pic_send_eoi(uint8_t irq);
void pic_remap(uint8_t offset_master, uint8_t offset_slave);
void pic_disable(void);
void pic_set_irq_mask(uint8_t irq);
void pic_clear_irq_mask(uint8_t irq);

#endif // I386_PIC_H
