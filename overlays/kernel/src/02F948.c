/* KERNEL.XFF @ 0x02F948 (144 B) - Sg2ExPcmInit
 * Evidence: Sg2StPcmInit(0); clears 0x1B4 bytes at .bss+0x9BE20; for the four 0x1D4-byte PCM records at .bss+0x9BFD8: status = 2 and twelve fields zeroed (source order = image order); then Sg2ExPcmOutputCtrl(2); returns 0. UNCONFIRMED: field names, arity of Sg2StPcmInit/Sg2ExPcmOutputCtrl.
 */
struct PcmOutput {
    int status;
    int unk4;
    char pad8[4];
    int unkC;
    char pad10[4];
    int unk14;
    int unk18;
    int unk1C;
    char pad20[0x14];
    int unk34;
    char pad38[8];
    int unk40;
    char pad44[0xDC - 0x44];
    int unkDC;
    int unkE0;
    char padE4[0xF8 - 0xE4];
    int unkF8;
    char padFC[8];
    int unk104;
    char pad108[0x1A0 - 0x108];
    int unk1A0;
    char pad1A4[0x1D4 - 0x1A4];
};
extern char D_kernel_bss_9BE20[];
extern struct PcmOutput D_kernel_bss_9BFD8[4];
void Sg2StPcmInit(int a);
void *memset(void *p, int c, unsigned int n);
int Sg2ExPcmOutputCtrl(int a);

int Sg2ExPcmInit(void) {

    int i;

    Sg2StPcmInit(0);
    memset(D_kernel_bss_9BE20, 0, 0x1B4);
    for (i = 0; i < 4; i++) {
        D_kernel_bss_9BFD8[i].status = 2;
        D_kernel_bss_9BFD8[i].unk1A0 = 0;
        D_kernel_bss_9BFD8[i].unk18 = 0;
        D_kernel_bss_9BFD8[i].unk1C = 0;
        D_kernel_bss_9BFD8[i].unk34 = 0;
        D_kernel_bss_9BFD8[i].unk40 = 0;
        D_kernel_bss_9BFD8[i].unkDC = 0;
        D_kernel_bss_9BFD8[i].unkE0 = 0;
        D_kernel_bss_9BFD8[i].unkF8 = 0;
        D_kernel_bss_9BFD8[i].unk104 = 0;
        D_kernel_bss_9BFD8[i].unk4 = 0;
        D_kernel_bss_9BFD8[i].unkC = 0;
        D_kernel_bss_9BFD8[i].unk14 = 0;
    }
    Sg2ExPcmOutputCtrl(2);
    return 0;
}
