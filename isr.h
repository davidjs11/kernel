/// isr.h ///////////////////////////////////////////////////////////

#ifndef ISR_H
#define ISR_H

#include "utils.h"

#define ISR_NUMBER 48

typedef struct {
    uint32_t ds;                                     // data segment
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // pusha 
    uint32_t int_no, err_code;                       // interrupt info 
    uint32_t eip, cs, eflags, useresp, ss;           // pushed by cpu
} regs_t;

static void (*isr_stub_table[ISR_NUMBER])(regs_t regs);

// install an isr handler
void isr_install(uint32_t i, void (*handler)(regs_t));

// init isr
void isr_init();

#endif // ISR_H
