/* asm/cod/028630.s -> _sbrk_r.
 * _sbrk_r (SHN_ABS)
 * MATCHED (Session 12). */
extern int D_0013A180[];

int sbrk(int incr);

int _sbrk_r(int *ptr, int incr) {
    int ret;
    int *p = &D_0013A180[3];

    *p = 0;
    if ((ret = sbrk(incr)) == -1 && *p != 0)
        *ptr = *p;
    return ret;
}
