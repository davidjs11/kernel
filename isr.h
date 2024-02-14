/// isr.h ///////////////////////////////////////////////////////////

#ifndef ISR_H
#define ISR_H

#include "utils.h"

#define ISR_NUMBER 48

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t int_no, err_code;
    uint32_t eip, cs, eflags, useresp, ss;
} regs_t;

typedef void (*isr_t)(regs_t);

// TODO
void isr_init();

// TODO
void isr_handler();

// TODO
void isr_install(size_t i, isr_t handler);

// TODO
void exception_handler(regs_t);

#endif // ISR_H
