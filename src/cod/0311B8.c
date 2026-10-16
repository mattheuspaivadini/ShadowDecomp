/* asm/cod/0311B8.s -> _lseek_r.
 * _lseek_r cc=296
 * MATCHED (Session 12). */
extern int D_0013A180[];

int lseek(int fd, int offset, int whence);

int _lseek_r(int *ptr, int fd, int offset, int whence) {
    int ret;
    int *p = &D_0013A180[3];

    *p = 0;
    if ((ret = lseek(fd, offset, whence)) == -1 && *p != 0)
        *ptr = *p;
    return ret;
}
