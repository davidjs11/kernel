/// string.c ////////////////////////////////////////////////////////

#include "string.h"

void *memset(void *src, uint8_t val, size_t n) {
    while(n--) ((uint8_t *) src)[n] = val;
    return src;
}

void *memcpy(void *dest, const void *src, size_t n) { 
    while(n--) ((uint8_t *) dest)[n] = ((uint8_t *) src)[n];
    return dest;
}

size_t strlen(const char *str) { 
    size_t len = 0;
    while(str[++len]);
    return len;
}

char *strcpy(char *dest, const char *src) { 
    size_t n = 0;
    while(src[n]) {
        dest[n] = src[n];
        n++;
    }
    dest[n] = '\0';
    return dest;
}

char *strncpy(char *dest, const char *src, size_t n) { 
    size_t i = 0;
    while(src[i] && i < n) {
        dest[i] = src[i];
        i++;
    }
    while(i < n) dest[i++] = 0x00;
    return dest;
}

int strcmp(const char *str1, const char *str2) {
    size_t n = 0;
    while(str1[n] && (str1[n] == str2[n])) n++;
    return str1[n] - str2[n];
}

