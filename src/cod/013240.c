/* asm/cod/013240.s -> sceVif1PkCloseGifTag.
 * SCE libvifpk/libdma (cc=29)
 * MATCHED. */
struct S013240 {
    unsigned int *write;   /* 0x00 */
    char pad04[0x10];
    unsigned int *last;    /* 0x14 */
};

void sceVif1PkCloseGifTag(struct S013240 *p) {
    unsigned int *last;
    unsigned int *write;
    unsigned int *q;
    unsigned long long v;
    unsigned int n;
    unsigned long t;
    unsigned int sz;

    last = p->last;
    write = p->write;
    v = *(unsigned long long *)last;
    n = (unsigned long long *)write - (unsigned long long *)last - 2;
    t = (v >> 58) & 3;
    if (t != 1)
        n = n >> 1;
    if (t != 2) {
        sz = (unsigned int)(v >> 60);
        if (sz == 0)
            sz = 16;
        n = (n + sz - 1) / sz;
    }
    p->last = 0;
    *(unsigned long long *)last = v + (unsigned int)n;
    q = write;
    while ((unsigned int)q & 0xC) {
        *q = 0;
        q++;
    }
    p->write = q;
}
/* func_00113240 */
