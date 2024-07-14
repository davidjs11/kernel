/*   string.h   */

#ifndef LIBC_STRING_H
#define LIBC_STRING_H

#include <stddef.h>

int memcmp(const void *str1, const void *str2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *dest, const void *src, size_t n);
void *memset(void *dest, unsigned char val, size_t n);
size_t strlen(const char *src);

#endif // LIBC_STRING_H
