/* KERNEL.XFF @ 0x01FE40 (32 B) - Sg2DspGetMasterVolume
 * Evidence: returns word +0 of the 24-byte record for the core at .bss+0x7F5C8.
 */
struct DspEffect {
    int volL;
    int volR;
    int unk8;
    short unkC;
    short unkE;
    int delay;
    int feedback;
};
extern struct DspEffect D_kernel_bss_7F5C8[2];
int DIntr(void);
int EIntr(void);

int Sg2DspGetMasterVolume(int core) {
    return D_kernel_bss_7F5C8[core].volL;
}
