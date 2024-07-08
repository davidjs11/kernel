/*   kmain.c   */

void kmain(void) {
    unsigned char *videoMemory = (unsigned char *) 0xB8000;
    *videoMemory = 'B';
    while (1);
}
