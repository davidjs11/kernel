/*   entry.S   */
.code32

/* kernel entry point */
// .extern kmain
.global _start
_start:
    jmp kmain
    jmp .
