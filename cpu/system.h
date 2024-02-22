/// system.h ////////////////////////////////////////////////////////

#ifndef SYSTEM_H
#define SYSTEM_H

#include "util.h"
#include "isr.h"

// kernel panic
void panic(const char *err, regs_t regs);

#endif // SYSTEM_H
