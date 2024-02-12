/// idt.h ///////////////////////////////////////////////////////////

#ifndef IDT_H
#define IDT_H

#include <stdint.h>

/* MACROS */
#define IDT_MAX_DESCRIPTORS 256


/* STRUCTS */
// idt entry structure
typedef struct {
    uint16_t    isr_low;      /* lower 16 bits of isr address */
	uint16_t    kernel_cs;    /* code segment offset in gdt (0x08) */
	uint8_t     reserved;     /* set to zero */
	uint8_t     attributes;   /* type and attributes; see idt doc. */
	uint16_t    isr_high;     /* higher 16 bits of isr address */
} __attribute__((packed)) idt_entry_t;

// idtr value structure
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr_t;


/* FUNCTIONS */
// initialize idt
void idt_init();

// set an idt entry
void idt_set_entry(uint8_t index, void *isr, uint8_t flags);

// temporal exception handler
void tmp_exception_handler();


#endif // IDT_H
