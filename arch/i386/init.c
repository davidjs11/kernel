/*   init.c   */

#include <init.h>
#include <util.h>
#include <tty.h>
#include <idt.h>
#include <isr.h>
#include <pic.h>
#include <irq.h>
#include <stdio.h>

typedef struct SMAP_entry {
	uint32_t base_low;
	uint32_t base_high;
	uint32_t length_low;
	uint32_t length_high;
	uint32_t type;
	uint32_t acpi;
}__attribute__((packed)) smap_entry_t;

const char *smap_entry_types[3] = {
    [0] = "undefined",
    [1] = "usable",
    [2] = "reserved",
};

void init_sys(void) {
    /* interrupts */
    pic_remap(0x20, 0x28);
    isr_init();
    idt_init();

    /* memory map */
    int num = *((int *) 0x8000);
    printf("-- memory map --\n");
    for (size_t i = 0; i <= num; i++) {
        printf("entry %d: ", i);
        smap_entry_t entry;
        entry = *(((smap_entry_t *) 0x8004)+i);

        // base address
        uint64_t base = (entry.base_high);
        base = (base << 32) | entry.base_low;
        printf("0x%x-", base);

        // length
        uint64_t length = (entry.length_high);
        length = (length << 32) | entry.length_low;
        printf("0x%x  ", base+length-1);

        // type
        printf("%s", smap_entry_types[entry.type]);

        printf("\n");
    }


    printf("\n");
}
