/*   pmm.h   */

#ifndef KERNEL_PMM_H
#define KERNEL_PMM_H

#include <stdint.h>
#include <stddef.h>

void pmm_init(size_t size, uint8_t *map);
void *pmm_alloc();
void pmm_free(void *addr);

#endif // KERNEL_PMM_H