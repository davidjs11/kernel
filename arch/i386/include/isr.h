/*   isr.h   */

#ifndef ARCH_ISR_H
#define ARCH_ISR_H

#include <util.h>

#define ISR_NUM     48

/* defined in entry.S */
extern void isr_0(regs_t);
extern void isr_1(regs_t);
extern void isr_2(regs_t);
extern void isr_3(regs_t);
extern void isr_4(regs_t);
extern void isr_5(regs_t);
extern void isr_6(regs_t);
extern void isr_7(regs_t);
extern void isr_8(regs_t);
extern void isr_9(regs_t);
extern void isr_10(regs_t);
extern void isr_11(regs_t);
extern void isr_12(regs_t);
extern void isr_13(regs_t);
extern void isr_14(regs_t);
extern void isr_15(regs_t);
extern void isr_16(regs_t);
extern void isr_17(regs_t);
extern void isr_18(regs_t);
extern void isr_19(regs_t);
extern void isr_20(regs_t);
extern void isr_21(regs_t);
extern void isr_22(regs_t);
extern void isr_23(regs_t);
extern void isr_24(regs_t);
extern void isr_25(regs_t);
extern void isr_26(regs_t);
extern void isr_27(regs_t);
extern void isr_28(regs_t);
extern void isr_29(regs_t);
extern void isr_30(regs_t);
extern void isr_31(regs_t);
extern void isr_32(regs_t);
extern void isr_33(regs_t);
extern void isr_34(regs_t);
extern void isr_35(regs_t);
extern void isr_36(regs_t);
extern void isr_37(regs_t);
extern void isr_38(regs_t);
extern void isr_39(regs_t);
extern void isr_40(regs_t);
extern void isr_41(regs_t);
extern void isr_42(regs_t);
extern void isr_43(regs_t);
extern void isr_44(regs_t);
extern void isr_45(regs_t);
extern void isr_46(regs_t);
extern void isr_47(regs_t);

typedef void (*isr_t)(regs_t);

void exception_handler(regs_t regs);
void isr_init(void);
void isr_install(size_t index, isr_t isr);
void isr_handler(regs_t regs);

#endif // ARCH_ISR_H
