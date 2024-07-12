/*   pic.c   */

#include <pic.h>
#include <ports.h>

void pic_send_eoi(uint8_t irq) {
    if (irq < 8) outb(PIC_MASTER_COMMAND, 0x20);
    else outb(PIC_SLAVE_COMMAND, 0x20);
}

void pic_remap(uint8_t offset_master, uint8_t offset_slave) {

    // get mask registers
    uint8_t mask_master, mask_slave;
    mask_master = inb(PIC_MASTER_DATA);
    mask_slave  = inb(PIC_SLAVE_DATA);

    // issue init command
    outb(PIC_MASTER_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    outb(PIC_SLAVE_COMMAND,  ICW1_INIT | ICW1_ICW4);
    io_wait();

    // set offsets
    outb(PIC_MASTER_DATA, offset_master);
    io_wait();
    outb(PIC_SLAVE_DATA,  offset_slave);
    io_wait();

    // configure cascade mode (slave is connected to master's irq 2)
    outb(PIC_MASTER_DATA, 0b0000100);
    io_wait();
    outb(PIC_SLAVE_DATA,  0b0000010);
    io_wait();

    // set 8086 mode
    outb(PIC_MASTER_COMMAND, ICW4_8086);
    io_wait();
    outb(PIC_SLAVE_COMMAND,  ICW4_8086);
    io_wait();

    outb(PIC_MASTER_DATA, mask_master);
    outb(PIC_SLAVE_DATA,  mask_slave);
}

void pic_disable(void) {
    outb(PIC_MASTER_COMMAND, 0xFF);
    outb(PIC_SLAVE_COMMAND,  0xFF);
}

void pic_set_irq_mask(uint8_t irq) {
    /* TO-DO */
}

void pic_clear_irq_mask(uint8_t irq) {
    /* TO-DO */
}
