/*   init.c   */

#include <init.h>
#include <util.h>
#include <tty.h>
#include <idt.h>
#include <isr.h>
#include <pic.h>
#include <irq.h>
#include <stdio.h>
#include <smap.h>
#include <pmm.h>

const char *smap_entry_types[3] = {
    [SMAP_ENTRY_UNDEFINED]  = "undefined",
    [SMAP_ENTRY_USABLE]     = "usable   ",
    [SMAP_ENTRY_RESERVED]   = "reserved ",
};

extern void *kernel_start, *kernel_end;
void init_sys(void) {
    // interrupts
    pic_remap(0x20, 0x28);
    isr_init();
    idt_init();

    // memory map
    int num_regions = *((int *) 0x8000);
    printf("-- memory map --\n");
    size_t total_mem = 0, usable_mem = 0;
    for (size_t i = 0; i < num_regions; i++) {
        printf("entry %d: ", i);
        smap_entry_t entry;
        entry = *(((smap_entry_t *) 0x8004)+i);

        // base address
        uint64_t base = (entry.base_high);
        base = (base << 32) | entry.base_low;
        printf("0x%08x - ", base);

        // length
        uint64_t length = (entry.length_high);
        length = (length << 32) | entry.length_low;
        total_mem += length;
        if (entry.type == SMAP_ENTRY_USABLE)
            usable_mem += length;
        printf("0x%08x ", base+length-1);

        // type
        printf("\t%s", smap_entry_types[entry.type]);

        // size
        length /= 1024; // KB
        if (length > 1024) {
            length /= 1024; // MB
            printf("\t(%dMB) ", length);
        }
        else {
            printf("\t(%dKB) ", length);
        }

        printf("\n");
    }

    // physical memory
    size_t pmm_size = pmm_init(total_mem, (uint8_t *) &kernel_end);
    for (size_t i = 0; i < num_regions; i++) {
        smap_entry_t entry;
        entry = *(((smap_entry_t *) 0x8004)+i);

        // map only usable entries
        if (entry.type == SMAP_ENTRY_USABLE) {
            // length
            uint64_t length = (entry.length_high);
            length = (length << 32) | entry.length_low;

            // align length to page frame size
            length &= ~(pmm_get_frame_size() - 1);

            pmm_init_reg((void *) entry.base_low, length);
        }
    }
    printf("total memory size: %uMB\n", total_mem/1024/1024);

    // alloc kernel and pmm bitmap
    size_t kernel_size = (&kernel_end) - (&kernel_start);
    pmm_deinit_reg((uint32_t *) &kernel_start, kernel_size + pmm_size);
}
