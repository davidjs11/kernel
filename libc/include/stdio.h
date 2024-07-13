/*   stdio.h   */

#ifndef LIBC_STDIO_H
#define LIBC_STDIO_H

#include <stddef.h>

int printf(const char *format, ...);
int putchar(char c);
int puts(const char *);

#endif // LIBC_STDIO_H
