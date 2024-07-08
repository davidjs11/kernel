// TO-DO
//  [x] printing routine
//  [x] read disk
//  [x] finish enabling a20
//  [x] setup & load gdt
//  [x] enable protected mode
//  [x] jump into the kernel !!!

.code16
.globl _start
_start: call boot

boot:
    cli                     // disable interrupts for the moment
    movb %dl, boot_disk     // save boot disk number (provided by BIOS)

    /* setup segments and stack */
    movw %cs, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %ss
    movw $0x7C00, %sp
    movw %sp, %bp

    /* init message */
    movw $msg_init, %si
    call print

    /* enable A20 gate */
    movw $msg_a20, %si
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

    /* enable protected mode */
    movw $msg_pm, %si
    call print
    movl %cr0, %eax
    orl $0x01, %eax
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

    /* jump to the kernel */
    ljmp $0x8, $_start32

/* 32-bit code */
.code32
_start32:
    jmp .

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
