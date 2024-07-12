/*   isr.c   */

#include <tty.h>
#include <isr.h>
#include <idt.h>

isr_t handlers[ISR_NUM] = { 0 };

static const char *exception_msg[32] = {
    "divide by zero",
    "debug",
    "nmi",
    "breakpoint",
    "overflow",
    "oob",
    "invalid opcode",
    "no coprocessor",
    "double fault",
    "coprocessor segment overrun",
    "bad tss",
    "segment not present",
    "stack fault",
    "general protection fault",
    "page fault",
    "unrecognized interrupt",
    "coprocessor fault",
    "alignment check",
    "machine check",
    "reserved by intel",
    "reserved by intel",
    "reserved by intel",
    "reserved by intel",
    "reserved by intel",
    "reserved by intel",
    "reserved by intel",
    "reserved by intel",
    "reserved by intel",
    "reserved by intel",
    "reserved by intel"
};

void exception_handler(regs_t *regs) {
    // improvised handler
    tty_t tty;
    tty_init(&tty);
    tty_print(&tty, exception_msg[regs->int_no]);
    while(1) __asm__ volatile ("cli; hlt");
    // it doesn't do nothing :-)
    // soon it will panic the kernel heheheh
}

void isr_install(size_t index, isr_t isr) {
    handlers[index] = isr;
}

void isr_init(void) {
    // set entries
    idt_set_entry(0,  isr_0,  0x8E);
    idt_set_entry(1,  isr_1,  0x8E);
    idt_set_entry(2,  isr_2,  0x8E);
    idt_set_entry(3,  isr_3,  0x8E);
    idt_set_entry(4,  isr_4,  0x8E);
    idt_set_entry(5,  isr_5,  0x8E);
    idt_set_entry(6,  isr_6,  0x8E);
    idt_set_entry(7,  isr_7,  0x8E);
    idt_set_entry(8,  isr_8,  0x8E);
    idt_set_entry(9,  isr_9,  0x8E);
    idt_set_entry(10, isr_10, 0x8E);
    idt_set_entry(11, isr_11, 0x8E);
    idt_set_entry(12, isr_12, 0x8E);
    idt_set_entry(13, isr_13, 0x8E);
    idt_set_entry(14, isr_14, 0x8E);
    idt_set_entry(15, isr_15, 0x8E);
    idt_set_entry(16, isr_16, 0x8E);
    idt_set_entry(17, isr_17, 0x8E);
    idt_set_entry(18, isr_18, 0x8E);
    idt_set_entry(19, isr_19, 0x8E);
    idt_set_entry(20, isr_20, 0x8E);
    idt_set_entry(21, isr_21, 0x8E);
    idt_set_entry(22, isr_22, 0x8E);
    idt_set_entry(23, isr_23, 0x8E);
    idt_set_entry(24, isr_24, 0x8E);
    idt_set_entry(25, isr_25, 0x8E);
    idt_set_entry(26, isr_26, 0x8E);
    idt_set_entry(27, isr_27, 0x8E);
    idt_set_entry(28, isr_28, 0x8E);
    idt_set_entry(29, isr_29, 0x8E);
    idt_set_entry(30, isr_30, 0x8E);
    idt_set_entry(31, isr_31, 0x8E);
    idt_set_entry(32, isr_32, 0x8E);
    idt_set_entry(33, isr_33, 0x8E);
    idt_set_entry(34, isr_34, 0x8E);
    idt_set_entry(35, isr_35, 0x8E);
    idt_set_entry(36, isr_36, 0x8E);
    idt_set_entry(37, isr_37, 0x8E);
    idt_set_entry(38, isr_38, 0x8E);
    idt_set_entry(39, isr_39, 0x8E);
    idt_set_entry(40, isr_40, 0x8E);
    idt_set_entry(41, isr_41, 0x8E);
    idt_set_entry(42, isr_42, 0x8E);
    idt_set_entry(43, isr_43, 0x8E);
    idt_set_entry(44, isr_44, 0x8E);
    idt_set_entry(45, isr_45, 0x8E);
    idt_set_entry(46, isr_46, 0x8E);
    idt_set_entry(47, isr_47, 0x8E);

    // set exception handlers
    for (size_t i=0; i<32; i++)
        isr_install(i, exception_handler);
}

void isr_handler(regs_t *regs) {
    if (handlers[regs->int_no])
        handlers[regs->int_no](regs);
}
