/*   smap.h   */

#ifndef ARCH_SMAP_H
#define ARCH_SMAP_H

#define SMAP_ENTRY_UNDEFINED    0
#define SMAP_ENTRY_USABLE       1
#define SMAP_ENTRY_RESERVED     2

typedef struct SMAP_entry {
	uint32_t base_low;
	uint32_t base_high;
	uint32_t length_low;
	uint32_t length_high;
	uint32_t type;
	uint32_t acpi;
}__attribute__((packed)) smap_entry_t;

#endif // ARCH_SMAP_H
