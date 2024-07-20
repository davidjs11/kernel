/*   pmm.c   */

#include <pmm.h>
#include <util.h>
#include <string.h>
#include <stdio.h>

#define PAGE_SIZE   4096

struct {
    size_t  memsize;
    uint8_t *memmap;
    size_t  total_blocks;
    size_t  used_blocks;
} pmm;

/* bitmap management */
inline void pmm_bitmap_set(size_t frame) {
    if (frame > pmm.total_blocks) return;
    pmm.memmap[frame/8] |= (1 << frame%8);
}

inline void pmm_bitmap_unset(size_t frame) {
    if (frame > pmm.total_blocks) return;
    pmm.memmap[frame/8] &= ~(1 << frame%8);
}

inline bool pmm_bitmap_test(size_t frame) {
    if (frame > pmm.total_blocks) return false;
    return pmm.memmap[frame/8] & (1 << frame%8);
}

extern void *kernel_end;
void pmm_init(size_t size, uint8_t *map) {
    // init values for memory manager
    pmm.memsize = size;
    pmm.memmap = (uint8_t *) map;
    pmm.total_blocks = pmm.memsize / PAGE_SIZE;
    pmm.used_blocks = pmm.total_blocks;

    // some info
    printf("\n-- physical memory manager --\n");
    printf("memory size: %uB\n", size);
    printf("page frames: %u\n", pmm.memsize / PAGE_SIZE);
    printf("bitmap size: %u\n", pmm.total_blocks/8);

    // set all pages as allocated
    memset(pmm.memmap, 0xFF, pmm.total_blocks/8);

    pmm_bitmap_unset(0xCAFE); // (setting for testing purposes)
}

void *pmm_alloc() {
    size_t frame = 0;

    // search for a free page
    size_t i = 0;
    while (pmm.memmap[i] == 0xFF) i++;

    // get the free page index
    size_t j;
    for (j = 0; !frame && i < pmm.total_blocks/8; j++) {
        if (!(pmm.memmap[i] & (1 << j)))
            frame = i * 8 + j;
    }

    // set page frame as used and return it
    pmm_bitmap_set(frame);
    return (void *) (frame * PAGE_SIZE);
}
