/* func_001120F8 @ 0x001120F8 (0x28 bytes): store 5 through the pointer
 * returned by func_00127528, return -1. */
void *__errno(void);

int unlink(void) {
    int *p = (int *)__errno();

    *p = 5;
    return -1;
}
