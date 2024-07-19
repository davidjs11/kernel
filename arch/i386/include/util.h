/*   util.h   */

#ifndef I386_UTIL_H
#define I386_UTIL_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef struct {
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, __ignored, ebx, edx, ecx, eax;
    uint32_t int_no, err_no;
    uint32_t eip, cs, efl, esp, ss;
} regs_t;

#endif // I386_UTIL_H
