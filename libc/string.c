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
    while(i < n) dest[i++] = '\0';
    return dest;
}

char *strcat(char *dest, const char *src) {
    size_t i = 0, j = 0;
    while(dest[i] != '\0') i++;
    while(src[j] != '\0') dest[i++] = src[j++];
    dest[i] = '\0';
    return dest;
}

int strcmp(const char *str1, const char *str2) {
    size_t n = 0;
    while(str1[n] && (str1[n] == str2[n])) n++;
    return str1[n] - str2[n];
}

/* temporal */
char *itoa(uint32_t n, char *buffer, uint8_t base) {
    const char *digits = "0123456789ABCDEF";
    size_t i = 0;

    // get characters from number
    while(n) {
        buffer[i++] = digits[n%base];
        n /= base;
    }
    
    // if base = 16 -> fill with 0s
    if (base == 16) {
        while(i < 8) buffer[i++] = '0';
    }

    // reverse digits
    i--;
    for(size_t j=0; j<i; j++) {
        char tmp = buffer[i];
        buffer[i--] = buffer[j];
        buffer[j] = tmp;
    }


    return buffer;
}
