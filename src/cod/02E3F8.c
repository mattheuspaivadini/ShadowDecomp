/* asm/cod/02E3F8.s -> _fwalk.
 * _fwalk: exact newlib fwalk loop form
 * MATCHED (Session 12). */
struct _glue {
    struct _glue *_next;    /* 0x00 */
    int _niobs;             /* 0x04 */
    char *_iobs;            /* 0x08 */
};

struct _reent {
    char pad[0x1D8];
    struct _glue __sglue;
};

int _fwalk(struct _reent *ptr, int (*function)(void *)) {
    struct _glue *g;
    char *fp;
    int n;
    int ret = 0;

    for (g = &ptr->__sglue; g != 0; g = g->_next) {
        for (fp = g->_iobs, n = g->_niobs; --n >= 0; fp += 0x58) {
            if (*(short *)(fp + 0xC) != 0)
                ret |= (*function)(fp);
        }
    }
    return ret;
}
