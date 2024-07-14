/*   string.c   */

#include <string.h>

int memcmp(const void *str1, const void *str2, size_t n) {
    int dif = 0;
    for (size_t i=0; i<n && !dif; i++)
        dif = ((unsigned char *) str2)[i] - ((unsigned char *) str1)[i];
    return dif;
}

void *memcpy(void *dest, const void *src, size_t n) {
    for (size_t i=0; i<n; i++)
        ((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
    return dest;
}

void *memmove(void *dest, const void *src, size_t n) {
	if (dest < src)
		for (size_t i=0; i<n; i++)
			((unsigned char *) dest)[i] = ((unsigned char *) src)[i];
	else
		for (size_t i=n; i!=0; i--)
			((unsigned char *) dest)[i-1] = ((unsigned char *) src)[i-1];
	return dest;
}

void *memset(void *dest, unsigned char val, size_t n) {
    for (size_t i=0; i<n; i++)
        ((unsigned char *) dest)[i] = val;
    return dest;
}

size_t strlen(const char *src) {
    size_t len = 0;
    while (src[len]) len++;
    return len;
}
