/* KERNEL.XFF @ 0x012718 (172 B) - iosSetDCViewPort
 * Evidence: the record holds two 64-bit GS words at +0x60/+0x70 and
 * +0x80/+0x90 (each written twice), giftag ids at +0x68/+0x78 and +0x88/+0x98,
 * and the four viewport ints at +0x174..+0x180. The scaling word is
 * (0x800-x-w/2)<<4 in the low half and the y/h equivalent in the high half
 * (the /2 uses the srl/addu/sra idiom); the offset word is
 * x | (x+w-1)<<16 | y<<32 | (y+h-1)<<48. UNCONFIRMED: field names.
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

void iosSetDCViewPort(struct DcVp *p, int x, int y, int w, int h) {
    long long ofs, sca;
    int ox, oy, x1, y1;

    x1 = x + w - 1;
    oy = -y - h / 2 + 0x800;
    ox = -x - w / 2 + 0x800;
    y1 = y + h - 1;
    ofs = (long long)(ox << 4) | ((long long)(oy << 4) << 32);
    sca = x | ((long long)x1 << 16) | ((long long)y << 32) | ((long long)y1 << 48);
    p->q68 = 0x18;
    p->q78 = 0x19;
    p->q70 = ofs;
    p->q60 = ofs;
    p->q88 = 0x40;
    p->q98 = 0x41;
    p->x = x;
    p->y = y;
    p->w = w;
    p->h = h;
    p->q90 = sca;
    p->q80 = sca;
}
