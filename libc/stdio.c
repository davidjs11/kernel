/*   stdio.c   */

#include <stdio.h>
#include <tty.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

extern tty_t tty; // global tty

int putchar(char c) {
    tty_putchar(&tty, c);
    return c;
}

void int_to_str(int num, char *str) {
    // check if negative
    bool negative = num < 0;
    if (negative) num = -num;

    // create string
    char *start = str;
    do {
        *str++ = '0' + (num % 10);
        num /= 10;
    } while (num > 0);
    if (negative) *str++ = '-';
    *str = '\0';
    
    // reverse string
    for (char *p1 = start, *p2 = str - 1; p1 < p2; ++p1, --p2) {
        char temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
}

void uint_to_str(unsigned int num, char *str) {
    // create string
    char *start = str;
    do {
        *str++ = '0' + (num % 10);
        num /= 10;
    } while (num > 0);
    *str = '\0';
    
    // reverse string
    for (char *p1 = start, *p2 = str - 1; p1 < p2; ++p1, --p2) {
        char temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
}

void hex_to_str(unsigned int num, char *str) {
    // create string
    const char *hex_digits = "0123456789ABCDEF";
    char *start = str;
    if (num == 0) *str++ = '0';
    else
        while (num > 0) {
            unsigned int digit = num % 16;
            *str++ = hex_digits[digit];
            num /= 16;
        }
    *str = '\0';

    // reverse string
    for (char *p1 = start, *p2 = str - 1; p1 < p2; ++p1, --p2) {
        char temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
}

// poor implementation for the moment
int printf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    int len = strlen(format);
    for (size_t i = 0; i < len; i++) {
        if (format[i] == '\n')
            tty_newline(&tty);
        else if (format[i] == '\t')
            tty_tab(&tty);
        else if (format[i] == '%') {
            i += 1;
            if (i == len) break;

            // number of characters
            char char_num_text[16] = { 0 };
            size_t j = 0;
            while ('0' <= format[i] && format[i] <= '9') {
                char_num_text[j++] = format[i];
                i += 1;
                if (i == len) break;
            }
            size_t char_num = atoi(char_num_text);

            char formatted_str[1024] = { 0 };
            switch (format[i]) {
                /* % */
                case '%':
                    formatted_str[0] = '%';
                    break;
                /* int */
                case 'd':
                case 'i':
                    int_to_str(va_arg(args, int), formatted_str);
                    break;
                /* unsigned int */
                case 'u':
                    uint_to_str(va_arg(args, int), formatted_str);
                    break;
                /* hexadecimal */
                case 'x':
                    hex_to_str(va_arg(args, unsigned int), formatted_str);
                    break;
                /* string */
                case 's':
                    // horrible; i'll fix this sooner or later
                    char *str = va_arg(args, char *);
                    memcpy(formatted_str, str, strlen(str)%1024);
                    break;
                /* char */
                case 'c':
                    formatted_str[0] = ((char) va_arg(args, int));
                    break;
                /* octal */
                case 'o': break;
                /* double (not planned yet) */
                case 'f': break;
            }

            
            if (char_num) {
                formatted_str[char_num] = '\0';
                size_t format_len = strlen(formatted_str);
                if (format_len < char_num) {
                    memmove(formatted_str+(char_num-format_len), formatted_str, format_len);
                    memset(formatted_str, '0', char_num-format_len);
                }
            }

            printf(formatted_str);
        }
        else
            tty_putchar(&tty, format[i]);
    }

    va_end(args);
    return len;
}
