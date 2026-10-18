/* asm/cod/01C510.s -> func_0011C510.
 * result decoder of func_0011C4C8: r pinned in $a0 (register asm), error-path -1 materialised as lui/ori (UNCONFIRMED asm pair) (Session 23)
 * MATCHED. */
int func_0011C4C8(int a0, int a1, int *a2);
int func_0011C510(int a0, int a1, int *a2) {
    register unsigned int r asm ("$4");

    r = func_0011C4C8(a0, a1, a2);
    if (*a2 != 0)
        return 0;
    if (r == 0xFFFFFFFFU) {
        unsigned int c;
        *a2 = 0x81010059;
        __asm__ ("lui %0, 0xFFFF" : "=r" (c));
        __asm__ ("ori %0, %0, 0xFFFF" : "+r" (c));
        return c;
    }
    return r & 0x7FFFFFFF;
}
