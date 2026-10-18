/* asm/cod/01CA30.s -> func_0011CA30.
 * FAT chain length walk; loop entered by goto with the n++/mask step at the top, direct returns for error/end/invalid (Session 23)
 * MATCHED. */
int func_0011C4C8(int a0, unsigned int a1, int *err);
int func_0011CA30(int a0, unsigned int a1) {
    int err;
    int n;
    int res;

    if (a1 == 0xFFFFFFFFU)
        return 0;
    n = 1;
    goto start;
    for (;;) {
        n++;
        a1 &= 0x7FFFFFFF;
    start:
        a1 = func_0011C4C8(a0, a1, &err);
        if (err != 0)
            return err;
        if (a1 == 0xFFFFFFFFU)
            return n;
        if ((int)a1 >= 0)
            return 0x81019002;
    }
}
