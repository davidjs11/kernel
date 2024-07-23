/*   paging.h   */

#ifndef I386_PAGING_H
#define I386_PAGING_H

#include <stdint.h>
#include <stdbool.h>

typedef struct page {
    uint32_t present    : 1;  /* present flag */
    uint32_t writable   : 1;  /* 0: read-only - 1: read-write */
    uint32_t usermode   : 1;  /* 0: kernel mode - 1: user mode */
    uint32_t accessed   : 1;  /* page has been accessed (setup by cpu) */
    uint32_t dirty      : 1;  /* page has been modified (setup by cpu) */
    uint32_t unused     : 7;  /* reserved by intel */
    uint32_t frame      : 20; /* frame (4k aligned) */
} page_t;

page_t page_setup(uint32_t frame, bool present, bool rw, bool usermode);

#endif // I386_PAGING_H
