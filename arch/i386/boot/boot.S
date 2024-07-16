/*   boot.S   */

.code16
.globl _start
_start:
    cli                     // disable interrupts for the moment
    movb %dl, boot_disk     // save boot disk number (provided by BIOS)

    /* setup segments and stack */
    movw %cs, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw $0x7C00, %sp
    movw %sp, %bp

    /* set video mode to TTY */
    xorb %ah, %ah
    movb $0x03, %al
    int $0x10

    /* init message */
    movw $msg_init, %si
    call print

    /* enable A20 gate */
    movw $msg_a20, %si  // not the best method :-(
    call print
    inb $0x92, %al
    orb $0x02, %al
    outb %al, $0x92

    /* read disk and load kernel at 0x10000 */
    movw $msg_disk, %si
    call print
    movw $1, %cx            // read cx * sector_num sectors in total
    movw $disk_packet, %si  // prepare for bios call
    movb boot_disk, %dl
    movw $0x1000, segment
    movw $0x1, sector_low
disk_read_loop:
    movb $0x42, %ah
    int $0x13

    addw $64, sector_low    // 64 sectors have been read
    addw $0x8000, offset    // offset += 0x40*0x200 (64 * 512B)
    jnc same_segment        // if not carry -> don't increment segment

    addw $0x1000, segment   // increment segment
    movw $0x0000, offset    // restart offset
same_segment:
    loop disk_read_loop     // loop until cx = 0

    /* get system memory map */
    call e820

    /* enable protected mode */
    movw $msg_pm, %si
    call print
    movl %cr0, %eax
    or $0x01, %eax
    movl %eax, %cr0

    /* load GDT */
    lgdt gdt_pointer
    movw $(gdt_data - gdt_start), %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %gs
    movw %ax, %fs
    movw %ax, %ss
    movl $0x2000, %esp

    /* 32-bit code */
    ljmp $0x8, $_start32
.code32
_start32:
    /* jump to the kernel */
    movl $0x10000, %eax
    jmpl *%eax

/* printing routine */
.code16
print:
    pusha
    xorb %bh, %bh
    movb $0x0E, %ah
print_loop:
    lodsb
    int $0x10
    testb %al, %al
    jz print_end
    jmp print_loop
print_end:
    popa
    ret

/* get system memory map at 0x80000 */
e820:
    movl $0xE820, %eax      // query system address map
    movw $0x8004, %di       // dest. buffer
    xorl %ebx, %ebx         // start from 0
    xorw %bp, %bp           // bp -> entry counter
    movl $24, %ecx          // ask for 24B entries
    movl $1, %es:20(%di)    // ACPI signature
    movl $0x534D4150, %edx  // SMAP function
    int $0x15
    jc e820_error
    movl $0x534D4150, %edx  // SMAP again (some BIOS delete this)
    cmp %eax, %edx          // eax != SMAP -> error
    jne e820_error
    testl %ebx, %ebx        // ebx = 0 -> only 1 entry long // ???
    je e820_error
    jmp e820_jmpin
e820_loop:
    movl $0xE820, %eax
    movl $24, %ecx          // ask for 24 bytes
    movl $1, %es:20(%di)    // some acpi thing i dont understand
    int $0x15
    jc e820_end             // CF = 1 -> finished
    movl $0x534D4150, %edx  // SMAP (again, some BIOS delete this)
e820_jmpin:
    jcxz e820_skipentry     // (length is zero)
    cmp $20, %cx            // got a 24 byte entry?
e820_notext:
    movl %es:8(%di), %ecx   // memory region length (lower 32)
    orl %es:12(%di), %ecx   // or with upper 32
    jz e820_skipentry       // if length is zero -> skip
    inc %bp
    add %di, 24
e820_skipentry:
    test %ebx, %ebx         // ebx = 0 -> operation complete
    jne e820_loop
e820_end:
    movw %bp, 0x8000        // store number of entries
    clc
    ret
e820_error:
    jmp e820_error 
// thank god osdev wiki exists

/* disk reading packet */
.align 4
disk_packet:    .byte 0x10        // size of the packet (16 bytes)
                .byte 0x00        // always 0
sector_num:     .word 0x0040      // number of sectors to read (64)
offset:         .word 0x0000      // offset of buffer in segment
segment:        .word 0x0000      // buffer segment
sector_low:     .long 0x00000000  // lower 32-bits from lba address
sector_high:    .long 0x00000000  // upper 16-bits from lba address

/* GDT */
.align 16
gdt_start:
gdt_null:       .quad 0x0000000000000000
gdt_code:       .quad 0x00CF9A000000FFFF
gdt_data:       .quad 0x00CF92000000FFFF
gdt_pointer:    .word . - gdt_start - 1
                .long gdt_start

/* other data */
boot_disk:      .word 0x0000
msg_init:       .asciz "initializing."
msg_disk:       .asciz "reading disk."
msg_a20:        .asciz "enabling a20 gate."
msg_pm:         .asciz "enabling protected mode."

/* MBR boot signature */
.fill 510-(.-_start), 1, 0x00
.word 0xAA55
