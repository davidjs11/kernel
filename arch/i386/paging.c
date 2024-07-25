/*   paging.c   */

#include <paging.h>
#include <pmm.h>

// nothing functional for the moment, just ideas :-(

// allocate a page entry in memory
void alloc_page(ptable_entry_t *entry) {
    // allocate a frame in physical memory
    // set a page table entry and map it to the frame
}

// free a page entry in memory
void free_page(ptable_entry_t *entry) {
    // free page frame
    // unset page table entry
}

// get page entry 
ptable_entry_t *get_entry() { }

// get page table
pdir_entry_t *get_table() { }

// flush tlb
void tlb_flush() { }

// map page
void map_page(void *physical, void *virtual) { }

// init 
void init(void) {
    // allocate default page table
    // allocate kernel page table (mapped to 0xC0000000, 3GB higher-half)
    // clear page tables
    // map pages
    // create default directory table
    // clear directory table
    // setup directory table (for default and kernel page tables)
    // store current PDBR
    // switch to page directory
    // enable paging
    // thanks brokenthorn.com for this !!
}

// don't forget page faults !
