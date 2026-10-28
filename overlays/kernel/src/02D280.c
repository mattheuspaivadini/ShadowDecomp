/* KERNEL.XFF @ 0x02D280 (132 B) - Sg2StAdpcmOpen
 * Evidence: Sg2RemoteSend(0x18, ch << 24 | addr & 0xFF0000 | +0x14 & 0xFF00 | (+0x10 & 0xFF0000) >> 16, +0x10 << 16 | (+0xC >> 8) & 0xFFFF, +0xC << 24 | +8 & 0xFFFFFF) - the first word built with |= statements; returns 0. UNCONFIRMED: parameter field names.
 */
struct Sg2StAdpcmParam {
    unsigned char ch;
    char pad1[3];
    unsigned int addr;
    unsigned int size;
    unsigned int unkC;
    unsigned int unk10;
    unsigned int unk14;
};
int Sg2RemoteSend(int cmd, int a, int b, int c);
int Sg2StAdpcmOpen(struct Sg2StAdpcmParam *p) {
 unsigned int a, b, c;
 a = p->ch << 24;
 a |= p->addr & 0xFF0000;
 a |= p->unk14 & 0xFF00;
 a |= (p->unk10 & 0xFF0000) >> 16;
 b = (p->unk10 << 16) | ((p->unkC >> 8) & 0xFFFF);
 c = (p->unkC << 24) | (p->size & 0xFFFFFF);
 Sg2RemoteSend(0x18, a, b, c);
 return 0;
}
