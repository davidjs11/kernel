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
static inline void pmm_bitmap_set(size_t frame) {
    if (frame > pmm.total_blocks) return;
    pmm.memmap[frame/8] |= (1 << frame%8);
}

static inline void pmm_bitmap_unset(size_t frame) {
    pmm.memmap[frame/8] &= ~(1 << frame%8);
}

static inline bool pmm_bitmap_test(size_t frame) {
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

    // set all pages as allocated
    memset(pmm.memmap, 0xFF, pmm.total_blocks/8);
}

void *pmm_alloc() {
    // if there isn't a free page frame, return NULL
    if (pmm.used_blocks == pmm.total_blocks) return NULL;

    // search for a free page frame
    size_t i = 0;
    while (pmm.memmap[i] == 0xFF) i++;
    if (i == pmm.total_blocks/8) return NULL;

    // get the free page frame index
    size_t frame = 0;
    size_t j;
    for (j = 0; !frame; j++) {
        if (!(pmm.memmap[i] & (1 << j)))
            frame = i * 8 + j;
    }

    // set page frame as used and return it
    pmm_bitmap_set(frame);
    pmm.used_blocks++;
    return (void *) (frame * PAGE_SIZE);
}

void pmm_free(void *addr) {
    size_t frame = (size_t) addr / PAGE_SIZE;
    if (0 < frame && frame < pmm.total_blocks) {
        pmm_bitmap_unset(frame);
        pmm.used_blocks--;
    }
}

volatile void pmm_init_reg(uint32_t * base, size_t size) {
    uint32_t frame = ((size_t) base / PAGE_SIZE);
    uint32_t blocks = size / PAGE_SIZE;

    // zero page
    if (frame == 0) {
        frame++;
        blocks--;
    }

    while (blocks--) {
        pmm_bitmap_unset(frame++);
        pmm.used_blocks--;
    }
}
