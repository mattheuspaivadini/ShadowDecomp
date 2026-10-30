/* KERNEL.XFF @ 0x01E608 (88 B) - sndVabHDOpen
 * Evidence: stores the size (+0x8) and the addr (+0xC) before/around
 * Sg2VabHdOpen(addr), stores its result at +0x4, returns on a negative handle,
 * and tail-jumps to Sg2VabBdOpen(hd, vab->bd) when +0x10 is non-zero.
 * The function is *void*: the image never moves the handle into $v0 on any
 * path (the negative path just restores and returns), which is what keeps the
 * handle in $v0/$a0 as the image does.
 * UNCONFIRMED: struct/field names, callee prototypes.
 */
typedef struct SndVab {
    int unk0;    /* 0x0  untouched here */
    int hd;      /* 0x4  Sg2VabHdOpen result */
    int size;    /* 0x8 */
    void *addr;  /* 0xc */
    void *bd;    /* 0x10 second Sg2VabBdOpen argument when non-NULL */
} SndVab;

extern int Sg2VabHdOpen(void *addr);
extern int Sg2VabBdOpen(int hd, void *bd);

void sndVabHDOpen(SndVab *vab, void *addr, int size) {
    int hd;

    vab->size = size;
    vab->addr = addr;
    hd = Sg2VabHdOpen(addr);
    vab->hd = hd;
    if (hd < 0)
        return;
    if (vab->bd != 0) {
        Sg2VabBdOpen(hd, vab->bd);
        return;
    }
}
