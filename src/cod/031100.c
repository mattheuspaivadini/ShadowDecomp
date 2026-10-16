/* asm/cod/031100.s -> _close_r.
 * _close_r (SHN_ABS)
 * MATCHED (Session 12). */
extern int D_0013A180[];

int close(int fd);

int _close_r(int *ptr, int fd) {
    int ret;
    int *p = &D_0013A180[3];

    *p = 0;
    if ((ret = close(fd)) == -1 && *p != 0)
        *ptr = *p;
    return ret;
}
