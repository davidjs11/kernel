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

extern void *kernel_end;
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

    printf("total memory: %dMB (usable: %dMB)\n",
           total_mem/1024/1024, usable_mem/1024/1024);

    // physical memory
    pmm_init(total_mem, (uint8_t *) &kernel_end);
    for (size_t i = 0; i < num_regions; i++) {
        smap_entry_t entry;
        entry = *(((smap_entry_t *) 0x8004)+i);

        // length
        uint64_t length = (entry.length_high);
        length = (length << 32) | entry.length_low;

        if (entry.type == SMAP_ENTRY_USABLE) {
            printf("initializing region %d\n", i);
            pmm_init_reg((void *) entry.base_low, length);
        }
    }
}
