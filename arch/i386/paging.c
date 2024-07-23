/*   paging.c   */

#include <paging.h>

page_t page_setup(uint32_t frame, bool present, bool rw, bool usermode) {
    page_t page;
    page.present = present;
    page.writable = rw;
    page.usermode = usermode;
    page.frame = frame;
    return page;
}
