/// string.h ////////////////////////////////////////////////////////

#ifndef STRING_H
#define STRING_H

#include <stddef.h>
#include <stdint.h>

/* ARRAY FUNCTIONS */
void *memset(void *src, uint8_t val, size_t n);
void *memcpy(void *dest, const void *src, size_t n);

/* STRING FUNCTIONS */
size_t strlen(const char *str);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);
int strcmp(const char *str1, const char *str2);
char *strcat(char *dest, const char *src);

// temporal
char *itoa(uint32_t n, char *buffer, uint8_t base);

#endif // STRING_H
