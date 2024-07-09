/*   entry.S   */
.code32

/* kernel entry point */
.global _start
_start:
    jmp kmain
    jmp .
