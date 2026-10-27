/* KERNEL.XFF @ 0x02F1B8 (76 B) - Sg2ExPcmInputSetPhase
 * Evidence: record[ch].+0x1B4 = r and +0x1B0 = l through one record pointer, then the update call. The four PCM input channels are 0x1D4-byte records at .bss+0x9BFD8 (index checked unsigned < 4); the static at .text+0x2F0A0 pushes the new parameters. UNCONFIRMED: field names.
 */
struct PcmFilter {
    int a[13];
};
struct PcmInput {
    char pad000[4];
    char filter[0x10];
    int lipFrame;
    char pad018[0x14C];
    int outputMode;
    int vol;
    char pad16C[0x10];
    int pan;
    int realPlayFrameCount;
    char pad184[0x2C];
    int phaseL;
    int phaseR;
    char pad1B8[0x1C];
};
extern struct PcmInput D_kernel_bss_9BFD8[4];
void func_02F0A0(unsigned int ch);

void Sg2ExPcmInputSetPhase(unsigned int ch, int l, int r) {
    if (ch < 4) {
        struct PcmInput *p = &D_kernel_bss_9BFD8[ch];

        p->phaseL = l;
        p->phaseR = r;
        func_02F0A0(ch);
    }
}
