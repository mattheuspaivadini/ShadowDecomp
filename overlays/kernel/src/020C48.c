/* KERNEL.XFF @ 0x020C48 (128 B) - Sg2ExStAdpcmStop
 * Evidence: unless .bss+0x7F5FC is set, the reserve flag [i] (.bss+0x7F600) = 1 for every voice bit of the u64 at +0xA0 (loaded once; literal 1L); state = 0; -1 for an old state < 0x10, else Sg2StAdpcmStop(voice) as a tail call.
 */
struct ExStAdpcm {
    int state;
    char pad4[0x9C];
    unsigned long voice;
};
extern int D_kernel_bss_7F5FC;
extern int D_kernel_bss_7F600[48];
int Sg2StAdpcmStop(unsigned long voice);
int Sg2ExStAdpcmStop(struct ExStAdpcm *w) {
    unsigned long i;

    unsigned long voice;
    int state;

    if (D_kernel_bss_7F5FC == 0) {
        voice = w->voice;
        i = 0;

        for (; i < 48; i++) {
            if (voice & (1L << (int)i)) {
                D_kernel_bss_7F600[i] = 1;
            }
        }
    }
    if (w->state < 0x10) {
        w->state = 0;
        return -1;
    }
    w->state = 0;
    return Sg2StAdpcmStop(w->voice);
}
