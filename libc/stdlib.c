/*   stdlib.c   */

#include <stdlib.h>
#include <tty.h>

void abort(void) {
    tty_t tty;
    tty_init(&tty);
    tty_print(&tty, "system aborted :-(");
    __asm__ volatile ("cli; hlt");
}

int atoi(const char *str) {
    int sign = (str[0] == '-') ? -1 : 1;
    int num = 0;
    for (size_t i = (sign == -1); str[i] != '\0'; i++)
        num = num * 10 + str[i]-'0';
    return num * sign;
}
