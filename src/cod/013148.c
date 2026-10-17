/* asm/cod/013148.s -> sceVif1PkEnd.
 * SCE libvifpk/libdma (cc=29)
 * MATCHED. */
struct S013148 {
    int *field00;                   /* 0x00 write cursor */
    int  field04;                   /* 0x04 */
    int *field08;                   /* 0x08 block start */
    int *field0C;                   /* 0x0C block to credit */
};

int *sceVif1PkTerminate(struct S013148 *p);

void sceVif1PkEnd(struct S013148 *p, int tag) {
    int *q;
    int *r;

    r = sceVif1PkTerminate(p);
    q = p->field00;
    p->field08 = r;
    *q++ = tag | 0x70000000;
    p->field0C = 0;
    p->field00 = q + 1;
    *q = 0;
}
