/*   pmm.h   */

#ifndef KERNEL_PMM_H
#define KERNEL_PMM_H

#include <stdint.h>
#include <stddef.h>

size_t pmm_init(size_t size, uint8_t *map);
void *pmm_alloc(void);
void pmm_free(void *addr);
void pmm_init_reg(uint32_t * base, size_t size);
void pmm_deinit_reg(uint32_t * base, size_t size);
size_t pmm_get_frame_size(void);
size_t pmm_get_total_frames(void);
size_t pmm_get_used_frames(void);
size_t pmm_get_free_frames(void);

#endif // KERNEL_PMM_H
