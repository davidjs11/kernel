/*   link.ld   */

OUTPUT_FORMAT("binary")
ENTRY(_start)
SECTIONS    
{
    . = 0x10000;
    .text ALIGN(0x1000) : { *(.text) }
    .data ALIGN(0x1000) : { *(.data) }
    .bss  ALIGN(0x1000) : { *(.bss)  }
    kernel_end = .;
}
