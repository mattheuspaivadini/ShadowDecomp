/* func_001120F8 @ 0x001120F8 (0x28 bytes): store 5 through the pointer
 * returned by func_00127528, return -1. */
void *func_00127528(void);

int func_001120F8(void) {
    int *p = (int *)func_00127528();

    *p = 5;
    return -1;
}
