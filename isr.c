/// isr.c ///////////////////////////////////////////////////////////

#include "isr.h"
#include "vga.h"

extern void isr_stub_0(regs_t);
extern void isr_stub_1(regs_t);
extern void isr_stub_2(regs_t);
extern void isr_stub_3(regs_t);
extern void isr_stub_4(regs_t);
extern void isr_stub_5(regs_t);
extern void isr_stub_6(regs_t);
extern void isr_stub_7(regs_t);
extern void isr_stub_8(regs_t);
extern void isr_stub_9(regs_t);
extern void isr_stub_10(regs_t);
extern void isr_stub_11(regs_t);
extern void isr_stub_12(regs_t);
extern void isr_stub_13(regs_t);
extern void isr_stub_14(regs_t);
extern void isr_stub_15(regs_t);
extern void isr_stub_16(regs_t);
extern void isr_stub_17(regs_t);
extern void isr_stub_18(regs_t);
extern void isr_stub_19(regs_t);
extern void isr_stub_20(regs_t);
extern void isr_stub_21(regs_t);
extern void isr_stub_22(regs_t);
extern void isr_stub_23(regs_t);
extern void isr_stub_24(regs_t);
extern void isr_stub_25(regs_t);
extern void isr_stub_26(regs_t);
extern void isr_stub_27(regs_t);
extern void isr_stub_28(regs_t);
extern void isr_stub_29(regs_t);
extern void isr_stub_30(regs_t);
extern void isr_stub_31(regs_t);
extern void isr_stub_32(regs_t);
extern void isr_stub_33(regs_t);
extern void isr_stub_34(regs_t);
extern void isr_stub_35(regs_t);
extern void isr_stub_36(regs_t);
extern void isr_stub_37(regs_t);
extern void isr_stub_38(regs_t);
extern void isr_stub_39(regs_t);
extern void isr_stub_40(regs_t);
extern void isr_stub_41(regs_t);
extern void isr_stub_42(regs_t);
extern void isr_stub_43(regs_t);
extern void isr_stub_44(regs_t);
extern void isr_stub_45(regs_t);
extern void isr_stub_46(regs_t);

// stub functions array
static void (*isr_stub_table[ISR_NUMBER])(regs_t regs) = {
    isr_stub_0,
    isr_stub_1,
    isr_stub_2,
    isr_stub_3,
    isr_stub_4,
    isr_stub_5,
    isr_stub_6,
    isr_stub_7,
    isr_stub_8,
    isr_stub_9,
    isr_stub_10,
    isr_stub_11,
    isr_stub_12,
    isr_stub_13,
    isr_stub_14,
    isr_stub_15,
    isr_stub_16,
    isr_stub_17,
    isr_stub_18,
    isr_stub_19,
    isr_stub_20,
    isr_stub_21,
    isr_stub_22,
    isr_stub_23,
    isr_stub_24,
    isr_stub_25,
    isr_stub_26,
    isr_stub_27,
    isr_stub_28,
    isr_stub_29,
    isr_stub_30,
    isr_stub_31,
    isr_stub_32,
    isr_stub_33,
    isr_stub_34,
    isr_stub_35,
    isr_stub_36,
    isr_stub_37,
    isr_stub_38,
    isr_stub_39,
    isr_stub_40,
    isr_stub_41,
    isr_stub_42,
    isr_stub_43,
    isr_stub_44,
    isr_stub_45,
    isr_stub_46
};

// called by common stub
void isr_handler(regs_t regs) {
    vga_print("hello from isr!", VGA_COLOR_RED);
    __asm__("hlt");
}
