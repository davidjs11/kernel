/*   pmm.c   */

#include <pmm.h>
#include <util.h>
#include <string.h>
#include <stdio.h>

#define PAGE_SIZE   4096

struct {
    size_t  memsize;
    uint8_t *memmap;
    size_t  total_frames;
    size_t  used_frames;
} pmm;

/* bitmap management */
static inline void pmm_bitmap_set(size_t frame) {
    if (frame > pmm.total_frames) return;
    pmm.memmap[frame/8] |= (1 << frame%8);
}

static inline void pmm_bitmap_unset(size_t frame) {
    pmm.memmap[frame/8] &= ~(1 << frame%8);
}

static inline bool pmm_bitmap_test(size_t frame) {
    if (frame > pmm.total_frames) return false;
    return pmm.memmap[frame/8] & (1 << frame%8);
}

extern void *kernel_end;
size_t pmm_init(size_t size, uint8_t *map) {
    // init values for memory manager
    pmm.memsize = size;
    pmm.memmap = (uint8_t *) map;
    pmm.total_frames = pmm.memsize / PAGE_SIZE;
    pmm.used_frames = pmm.total_frames;

    // set all pages as allocated
    memset(pmm.memmap, 0xFF, pmm.total_frames/8);

    // return size of pmm
    return pmm.total_frames / 8;
}

void *pmm_alloc(void) {
    // if there isn't a free page frame, return NULL
    if (pmm.used_frames == pmm.total_frames) return NULL;

    // search for a free page frame
    size_t i = 0;
    while (pmm.memmap[i] == 0xFF) i++;
    if (i == pmm.total_frames/8) return NULL;

    // get the free page frame index
    size_t frame = 0;
    size_t j;
    for (j = 0; !frame; j++) {
        if (!(pmm.memmap[i] & (1 << j)))
            frame = i * 8 + j;
    }

    // set page frame as used and return it
    pmm_bitmap_set(frame);
    pmm.used_frames++;
    return (void *) (frame * PAGE_SIZE);
}

void pmm_free(void *addr) {
    size_t frame = (size_t) addr / PAGE_SIZE;
    if (0 < frame && frame < pmm.total_frames) {
        pmm_bitmap_unset(frame);
        pmm.used_frames--;
    }
}

void pmm_init_reg(uint32_t * base, size_t size) {
    uint32_t frame = ((size_t) base / PAGE_SIZE);
    uint32_t frames = size / PAGE_SIZE;
    if (size % PAGE_SIZE) frames++; // upper bound

    // zero page
    if (frame == 0) {
        frame++;
        frames--;
    }

    while (frames--) {
        pmm_bitmap_unset(frame++);
        pmm.used_frames--;
    }
}

void pmm_deinit_reg(uint32_t * base, size_t size) {
    uint32_t frame = ((size_t) base / PAGE_SIZE);
    uint32_t frames = size / PAGE_SIZE;
    if (size % PAGE_SIZE) frames++; // upper bound

    while (frames--) {
        pmm_bitmap_set(frame++);
        pmm.used_frames++;
    }
}

size_t pmm_get_frame_size(void) {
    return PAGE_SIZE;
}

size_t pmm_get_total_frames(void) {
    return pmm.total_frames;
}

size_t pmm_get_used_frames(void) {
    return pmm.used_frames;
}

size_t pmm_get_free_frames(void) {
    return pmm.total_frames - pmm.used_frames;
}
