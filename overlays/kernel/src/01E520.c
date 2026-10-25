/* KERNEL.XFF @ 0x01E520 (88 B) - sndSepInit
 * Evidence: iosCreateSema(1, 1, 0) to .bss+0x7D1D0, then clears word 0 of the 32 0x70-byte slots at .bss+0x7C3D0 from the last one down. UNCONFIRMED: names/layout.
 */
struct SepSlot {
    int used;
    int unk4;
    unsigned long flags;
    char pad[0x60];
};
extern struct SepSlot D_kernel_bss_7C3D0[32];
extern int D_kernel_bss_7D1D0;
int iosCreateSema(int init, int max, int attr);

void sndSepInit(void) {
    int i;

    D_kernel_bss_7D1D0 = iosCreateSema(1, 1, 0);
    for (i = 31; i >= 0; i--) {
        D_kernel_bss_7C3D0[i].used = 0;
    }
}
