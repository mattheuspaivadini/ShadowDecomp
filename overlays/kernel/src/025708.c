/* KERNEL.XFF @ 0x025708 (172 B) - Sg2RemoteSendDmaCom
 * Evidence: writes {cmd, a, b, c} and result = -1 into the 32-entry 0x14-byte DMA command ring at .bss+0x96F40 at the write index (.bss+0x96F28), advances the index modulo 32 under DIntr/EIntr and returns the slot used. UNCONFIRMED: field names.
 */
struct Sg2RemoteDmaCmd {
    int cmd;
    int a;
    int b;
    int c;
    int result;
};
extern int D_kernel_bss_96F28;
extern struct Sg2RemoteDmaCmd D_kernel_bss_96F40[32];
int DIntr(void);
int EIntr(void);

int Sg2RemoteSendDmaCom(int cmd, int a, int b, int c) {
    int id = D_kernel_bss_96F28;
    int intr;

    D_kernel_bss_96F40[id].result = -1;
    D_kernel_bss_96F40[id].cmd = cmd;
    D_kernel_bss_96F40[id].a = a;
    D_kernel_bss_96F40[id].b = b;
    D_kernel_bss_96F40[id].c = c;
    intr = DIntr();
    D_kernel_bss_96F28 = (D_kernel_bss_96F28 + 1) % 32;
    if (intr) {
        EIntr();
    }
    return id;
}
