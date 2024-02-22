/// system.c ////////////////////////////////////////////////////////

#include "system.h"
#include "string.h"
#include "vga.h"

const char *panic_msg = "oh meu deus, panico do kernel!!!";

// local function for register printing
void print_reg(const char *name, uint32_t value, size_t row) {
    char buffer[32];
    strcpy(buffer, name);
    strcat(buffer, "0x");
    itoa(value, buffer+strlen(name)+2, 16);
    vga_print_at(buffer, VGA_TEXT_COLOR(VGA_BRIGHT_WHITE, VGA_BLUE),
                 VGA_ROWS/4+2+row, VGA_COLS/2-strlen(buffer)/2);
}

void panic(const char *err, regs_t regs) {
    // print message
    vga_clear(VGA_BLUE);
    vga_print_at(panic_msg, VGA_TEXT_COLOR(VGA_BLUE, VGA_BRIGHT_WHITE),
                 VGA_ROWS/8, VGA_COLS/2-strlen(panic_msg)/2);
    vga_print_at(err, VGA_TEXT_COLOR(VGA_BRIGHT_WHITE, VGA_BLUE),
                 VGA_ROWS/5, VGA_COLS/2-strlen(err)/2);

    // print registers
    print_reg("EAX: ", regs.eax, 0);
    print_reg("EBX: ", regs.ebx, 1);
    print_reg("ECX: ", regs.ecx, 2);
    print_reg("EDX: ", regs.edx, 3);
    print_reg("EIP: ", regs.eip, 5);
    print_reg("CS:  ", regs.cs,  6);
    print_reg("EDI: ", regs.edi, 7);
    print_reg("ESI: ", regs.esi, 8);
    
    // halt the cpu
    HLT();
}
