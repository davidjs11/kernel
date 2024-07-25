/*   paging.h   */

#ifndef I386_PAGING_H
#define I386_PAGING_H

#include <stdint.h>
#include <stdbool.h>

/* page table entries */
typedef struct {
    uint32_t present    : 1;    /* page is present in main memory */
    uint32_t writable   : 1;    /* page can be written */
    uint32_t usermode   : 1;    /* page can be used in user mode */
    uint32_t wthrough   : 1;    /* 0: write back - 1: write through */
    uint32_t cache      : 1;    /* 0: cached - 1: not cached */
    uint32_t accessed   : 1;    /* page has been accessed (set by cpu) */
    uint32_t dirty      : 1;    /* page has been modified (set by cpu) */
    uint32_t reserved   : 2;    /* reserved by intel */
    uint32_t available  : 3;    /* available for free use */
    uint32_t frame      : 20;   /* page frame (4K aligned) */
} ptable_entry_t;

/* page directory entries */
typedef struct {
    uint32_t present    : 1;    /* page is present in main memory */
    uint32_t writable   : 1;    /* page can be written */
    uint32_t usermode   : 1;    /* page can be used in user mode */
    uint32_t wthrough   : 1;    /* 0: write back - 1: write through */
    uint32_t cache      : 1;    /* 0: cached - 1: not cached */
    uint32_t accessed   : 1;    /* page has been accessed (set by cpu) */
    uint32_t dirty      : 1;    /* (ignored) */
    uint32_t page_size  : 1;    /* 0: 4KB - 1: 4MB */
    uint32_t ignored    : 1;    /* (ignored) */
    uint32_t available  : 3;    /* available for free use */
    uint32_t frame      : 20;   /* page frame (4K aligned) */
} pdir_entry_t;

typedef struct {
    ptable_entry_t entry[1024];
} ptable_t;

typedef struct {
    pdir_entry_t entry[1024];
} pdir_t;

void paging_init(void);

#endif // I386_PAGING_H
