/*   stdio.c   */

#include <stdio.h>
#include <tty.h>
#include <string.h>
#include <stdarg.h>

extern tty_t tty; // global tty

int putchar(char c) {
    tty_putchar(&tty, c);
    return c;
}

void int_to_str(int num, char *str) {
    bool negative = num < 0;
    if (negative) {
        num = -num;
    }
    
    char *start = str;
    do {
        *str++ = '0' + (num % 10);
        num /= 10;
    } while (num > 0);

    if (negative) {
        *str++ = '-';
    }

    *str = '\0';
    
    // Reverse the string
    for (char *p1 = start, *p2 = str - 1; p1 < p2; ++p1, --p2) {
        char temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
}

void uint_to_str(unsigned int num, char *str) {
    char *start = str;
    do {
        *str++ = '0' + (num % 10);
        num /= 10;
    } while (num > 0);

    *str = '\0';
    
    // Reverse the string
    for (char *p1 = start, *p2 = str - 1; p1 < p2; ++p1, --p2) {
        char temp = *p1;
        *p1 = *p2;
        *p2 = temp;
    }
}

// poor implementation for the moment
int printf(const char *format, ...) {
    va_list parameters;
    va_start(parameters, format);

    int len = strlen(format);
    for (size_t i = 0; i < len; i++) {
        if (format[i] == '\n')
            tty_move_cursor(&tty, tty.row+1, 0);
        else if (format[i] == '%') {
            i += 1;
            if (i == len) break;

            char str[32];
            switch (format[i]) {
                /* % */
                case '%':
                    putchar('%');
                    break;
                /* int */
                case 'd':
                case 'i':
                    int_to_str(va_arg(parameters, int), str);
                    printf(str);
                    break;
                /* unsigned int */
                case 'u':
                    uint_to_str(va_arg(parameters, int), str);
                    printf(str);
                    break;
                /* string */
                case 's':
                    printf(va_arg(parameters, char *));
                    break;
                /* char */
                case 'c':
                    putchar((char) va_arg(parameters, int));
                    break;

                /* octal */
                case 'o': break;
                /* hexadecimal */
                case 'x': break;
                /* double (not planned yet) */
                case 'f': break;
            }
        }
        else
            tty_putchar(&tty, format[i]);
    }

    return len;
}
