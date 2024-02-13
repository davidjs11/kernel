/// utils.h /////////////////////////////////////////////////////////

#ifndef UTILS_H
#define UTILS_H

#include <stdint.h>
typedef uint32_t size_t;

#define CLI(){__asm__("cli");}
#define STI(){__asm__("sti");}
#define HLT(){__asm__("hlt");}

#endif // UTILS_H
