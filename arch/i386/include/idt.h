/*   idt.h   */

#ifndef IDT_H
#define IDT_H

void function_test(void);

typedef struct {

} __attribute__((packed)) idt_entry;

/*idt_entry idt[256];*/

#endif // IDT_H
