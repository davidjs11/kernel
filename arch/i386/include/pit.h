/*   pit.h   */

#ifndef ARCH_PIT_H
#define ARCH_PIT_H

#define PIT_CLK_1               0x40
#define PIT_CLK_2               0x41
#define PIT_CLK_3               0x42
#define PIT_OCW                 0x43
#define PIT_OCW_MASK_MODE       0x0E
#define PIT_OCW_MASK_COUNTER    0xC0
#define PIT_CLK_HZ              1193180

#endif // ARCH_PIT_H
