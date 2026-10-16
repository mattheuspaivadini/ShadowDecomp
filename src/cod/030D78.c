/* asm/cod/030D78.s -> __submore.
 * Newlib __submore; authentic ungetc.c source, older fp->_data reent signature
 * MATCHED.
 *
 * The overlap copy goes to 0x0012821C, the image's `memcpy`
 * (`config/symbol_addrs.txt` keeps the identification in a comment; splat's own
 * label is `func_0012821C`, so that is the name used here). */
#define BUFSIZ_030D78 1024      /* newlib BUFSIZ == 0x400 (see the addiu 0x400) */

struct S30D78_ub {
    unsigned char *_base;   /* 0x30 */
    int            _size;   /* 0x34 */
};

struct S30D78 {
    unsigned char *_p;          /* 0x00 */
    char           pad04[0x2C]; /* 0x04 */
    struct S30D78_ub _ub;       /* 0x30 */
    unsigned char *_up;         /* 0x38 UNCONFIRMED: newlib `_up` */
    int            _ur;         /* 0x3C UNCONFIRMED: newlib `_ur` */
    unsigned char  _ubuf[3];    /* 0x40 */
    char           pad43[0x11]; /* 0x43 */
    void          *_data;       /* 0x54 the reent pointer */
};

extern void *_malloc_r(void *reent, unsigned int size);
extern void *_realloc_r(void *reent, void *ptr, unsigned int size);
extern void *func_0012821C(void *dst, const void *src, unsigned int n);

int __submore(struct S30D78 *fp)
{
    register int i;
    register unsigned char *p;

    if (fp->_ub._base == fp->_ubuf) {
        /* Get a new buffer (rather than expanding the old one). */
        if ((p = (unsigned char *)_malloc_r(fp->_data,
                                            (unsigned int)BUFSIZ_030D78)) == 0)
            return -1;
        fp->_ub._base = p;
        fp->_ub._size = BUFSIZ_030D78;
        p += BUFSIZ_030D78 - sizeof(fp->_ubuf);
        for (i = sizeof(fp->_ubuf); --i >= 0;)
            p[i] = fp->_ubuf[i];
        fp->_p = p;
        return 0;
    }

    i = fp->_ub._size;
    p = (unsigned char *)_realloc_r(fp->_data, (void *)fp->_ub._base, i << 1);
    if (p == 0)
        return -1;
    func_0012821C((void *)(p + i), (void *)p, (unsigned int)i);
    fp->_p = p + i;
    fp->_ub._base = p;
    fp->_ub._size = i << 1;
    return 0;
}
