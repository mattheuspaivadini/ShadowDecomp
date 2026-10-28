/* KERNEL.XFF @ 0x02E568 (160 B) - func_02E568 (static, no symbol in the shipped .symtab)
 * Evidence: PCM output transfer: the int callback at .bss+0x9C728 (0, buf (+8) + pos (+0x18), iop buffer (+0x1A4) + iop pos (+0x1AC), n * 2) on 16-bit samples; both positions advance by n and wrap with % (sizes +0x10 / +0x1A8). UNCONFIRMED: names; Ghidra FUN_0022e568.
 */
struct PcmOut {
    char pad0[8];
    short *buf;
    char padC[4];
    int size;
    char pad14[4];
    int pos;
    char pad1C[0x1A4 - 0x1C];
    short *iopbuf;
    int iopsize;
    int ioppos;
};
extern int (*D_kernel_bss_9C728)(int mode, short *src, short *dst, int size);

void func_02E568(struct PcmOut *o, int n) {
    D_kernel_bss_9C728(0, o->buf + o->pos, o->iopbuf + o->ioppos, n * 2);
    o->pos += n;
    o->pos %= o->size;
    o->ioppos += n;
    o->ioppos %= o->iopsize;
}
