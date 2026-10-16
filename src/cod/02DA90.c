/* asm/cod/02DA90.s -> fread.
 * Newlib fread; authentic source, non-reentrant __srefill(fp) variant
 * MATCHED.
 *
 * The two byte-copy calls go to 0x0012821C, which is the image's `memcpy`
 * (`config/symbol_addrs.txt` records the identification in a comment; splat's
 * own label is `func_0012821C`, so that is the name used here). */
typedef unsigned int size_t_02DA90;

struct S02DA90_FILE {
    unsigned char *_p;      /* 0x00 */
    int            _r;      /* 0x04 */
};

extern int __srefill(struct S02DA90_FILE *fp);
extern void *func_0012821C(void *dst, const void *src, size_t_02DA90 n);

size_t_02DA90 fread(void *buf, size_t_02DA90 size, size_t_02DA90 count,
                    struct S02DA90_FILE *fp)
{
    size_t_02DA90 resid;
    char *p;
    int r;
    size_t_02DA90 total;

    if ((resid = count * size) == 0)
        return 0;
    if (fp->_r < 0)
        fp->_r = 0;
    total = resid;
    p = (char *)buf;
    while (resid > (r = fp->_r)) {
        func_0012821C((void *)p, (void *)fp->_p, (size_t_02DA90)r);
        fp->_p += r;
        /* fp->_r = 0 ... done in __srefill */
        p += r;
        resid -= r;
        if (__srefill(fp)) {
            /* no more input: return partial result */
            return (total - resid) / size;
        }
    }
    func_0012821C((void *)p, (void *)fp->_p, resid);
    fp->_r -= resid;
    fp->_p += resid;
    return count;
}
