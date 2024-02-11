/// kernel.c ////////////////////////////////

#define VGA_ADDRESS_SPACE 0xB8000
#define VGA_COLUMN_COUNT 80
#define VGA_ROW_COUNT 50

void vga_clear(void) {
    for(int i = 0; i < VGA_COLUMN_COUNT * VGA_ROW_COUNT; i++) {
        ((volatile char *)0xB8000)[2*i]   = 0x00;
        ((volatile char *)0xB8000)[2*i+1] = 0x04;
    }
}

// print a string into the vga text buffer
void print_vga(const char *str, const char color) {
    volatile char *video = (volatile char *) 0xB8000;
    while(*str) {
        *video++ = *str++;
        *video++ = color;
    }
}

void main() {
    char *videoMemory = (char *) 0xB8000;
    vga_clear();
    print_vga("kernel.c loaded successfully", 0x04);
}
