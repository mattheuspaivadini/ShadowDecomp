/* KERNEL.XFF @ 0x021318 (212 B) - Sg2ExStAdpcmClose
 * Evidence: Sg2ExStAdpcmStop(w) for state >= 0x10; state = 0; Sg2StAdpcmClose(i) for every voice bit of the u64 at +0xA0 with the reserve flag [i] (.bss+0x7F600) set to 1 (64-bit literal 1L shares the register with the stored 1) and ret = 0; unless flags (+8) bit 1, the int callback at .bss+0x7F6C0 (w, 4, 0, 0); returns ret (-1 when no voice). UNCONFIRMED: names.
 */
struct ExStAdpcm {
    int state;
    int saved;
    int flags;
    char padC[0x94];
    unsigned long voice;
};
extern int D_kernel_bss_7F600[48];
extern int (*D_kernel_bss_7F6C0)(struct ExStAdpcm *w, int ev, int a, int b);
int Sg2ExStAdpcmStop(struct ExStAdpcm *w);
void Sg2StAdpcmClose(int ch);

int Sg2ExStAdpcmClose(struct ExStAdpcm *w) {
    unsigned long i;

    int ret = -1;

    if (w->state >= 0x10) {
        Sg2ExStAdpcmStop(w);
    }
    w->state = 0;
    i = 0;

    for (; i < 48; i++) {
        if (w->voice & (1L << (int)i)) {
            Sg2StAdpcmClose((int)i);
            ret = 0;
            D_kernel_bss_7F600[i] = 1;
        }
    }
    if (!(w->flags & 2)) {
        D_kernel_bss_7F6C0(w, 4, 0, 0);
    }
    return ret;
}
