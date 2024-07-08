/*   link.ld   */

OUTPUT_FORMAT("binary")
ENTRY(_start)
SECTIONS    
{
    . = 0x10000;
    .text ALIGN(4K) : { *(.text) }
    .data ALIGN(4K) : { *(.data) }
    .bss  ALIGN(4K) : { *(.bss)  }
    end = .;
}
