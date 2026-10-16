/* asm/cod/031158.s -> _fstat_r.
 * _fstat_r (SHN_ABS)
 * MATCHED (Session 12). */
extern int D_0013A180[];

int fstat(int fd, void *pstat);

int _fstat_r(int *ptr, int fd, void *pstat) {
    int ret;
    int *p = &D_0013A180[3];

    *p = 0;
    if ((ret = fstat(fd, pstat)) == -1 && *p != 0)
        *ptr = *p;
    return ret;
}
