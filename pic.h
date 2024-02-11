/// pic.h ///////////////////////////////////////////////////////////

#ifndef PIC_H
#define PIC_H


/* MACROS */
#define PIC1         0x20       /* io address for master pic */
#define PIC2         0xA0       /* io address for slave pic */
#define PIC1_COMMAND PIC1       /* command address */
#define PIC2_COMMAND PIC2
#define PIC1_DATA   (PIC1+1)    /* data address */
#define PIC2_DATA   (PIC2+1)
#define PIC_EOI      0x20       /* end of interrupt code */


/* FUNCTIONS */
void pic_init();
void pic_end_of_interrupt();

#endif // PIC_H
