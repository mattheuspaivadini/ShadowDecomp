/* KERNEL.XFF @ 0x0127C8 (132 B) - iosSetDCViewPortCenter
 * Evidence: `addu v0,a1,a3` / `addu t3,a2,t0` build x+w and y+h first, both -1
 * later; `dsll v0,16` + `dsll32 v1,a2,0` + ors give sca = x | (x+w-1)<<16 |
 * y<<32 | (y+h-1)<<48, stored to +0x80/+0x90; `addiu t2,0x800`/`sll 4` +
 * `addiu t1,0x800`/`sll 4` give ofs = (cx+0x800)<<4 | ((cy+0x800)<<4)<<32,
 * stored to +0x60/+0x70; +0x68=0x18, +0x78=0x19, +0x88=0x40, +0x98=0x41;
 * the four ints x/y/w/h go to +0x174..+0x180.
 * The two empty "+r" asms are scheduling barriers: they leave the apparent
 * order of the two independent sums as written (the only residue left
 * otherwise) and emit no code.
 * UNCONFIRMED: struct/field names, the 0x18/0x19/0x40/0x41 tags.
 */
struct DcVp {
    char pad0[0x60];
    long long q60;
    long long q68;
    long long q70;
    long long q78;
    long long q80;
    long long q88;
    long long q90;
    long long q98;
    char pad1[0x174 - 0xA0];
    int x, y, w, h;
};

void iosSetDCViewPortCenter(struct DcVp *p, int x, int y, int w, int h, int cx, int cy) {
    long long ofs, sca;

    ofs = (long long)((cx + 0x800) << 4) | ((long long)((cy + 0x800) << 4) << 32);
    {
        int y1;
        int x1 = x + w;
        __asm__ ("" : "+r"(x1));
        y1 = y + h;
        __asm__ ("" : "+r"(y1));
        x1 = x1 - 1;
        y1 = y1 - 1;
        sca = x | ((long long)x1 << 16) | ((long long)y << 32) |
              ((long long)y1 << 48);
    }
 p->q68 = 0x18;
 p->q78 = 0x19;
 p->q70 = ofs;
 p->q60 = ofs;
 p->q88 = 0x40;
 p->q98 = 0x41;
 p->x = x;
 p->q90 = sca;
 p->y = y;
 p->w = w;
 p->h = h;
 p->q80 = sca;
}
