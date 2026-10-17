/* asm/cod/0131A0.s -> sceVif1PkOpenDirectCode.
 * SCE libvifpk/libdma (cc=29)
 * MATCHED. */
struct S0131A0 {
    int *field00;                   /* 0x00 write cursor */
    int  field04;                   /* 0x04 */
    int *field08;                   /* 0x08 block start */
    int *field0C;                   /* 0x0C block to credit */
};

void sceVif1PkAlign(struct S0131A0 *p, int bit, int pos);

void sceVif1PkOpenDirectCode(struct S0131A0 *p, int irq) {
    int *q;

    sceVif1PkAlign(p, 2, 3);
    q = p->field00;
    p->field0C = q;
    *p->field00++ = irq ? 0xD0000000 : 0x50000000;
}
