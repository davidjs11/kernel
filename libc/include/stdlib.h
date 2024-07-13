/*   stdlib.h   */

#ifndef LIBC_STDLIB_H
#define LIBC_STDLIB_H

#include <stddef.h>

void abort(void);
int atoi(const char *str);
// long strol(const char *str, char **endptr, int base); // maybe won't do this right now

#endif // LIBC_STDLIB_H
