/* KERNEL.XFF @ 0x025678 (144 B) - Sg2RemoteSend
 * Evidence: writes {cmd, a, b, c} into the 512-entry 16-byte remote command ring at .bss+0x92D40 at the write index (.bss+0x92D00), then advances the index modulo 512 under DIntr/EIntr; returns 0. UNCONFIRMED: field names.
 */
struct Sg2RemoteCmd {
    int cmd;
    int a;
    int b;
    int c;
};
extern int D_kernel_bss_92D00;
extern struct Sg2RemoteCmd D_kernel_bss_92D40[512];
int DIntr(void);
int EIntr(void);

int Sg2RemoteSend(int cmd, int a, int b, int c) {
    int intr;

    D_kernel_bss_92D40[D_kernel_bss_92D00].cmd = cmd;
    D_kernel_bss_92D40[D_kernel_bss_92D00].a = a;
    D_kernel_bss_92D40[D_kernel_bss_92D00].b = b;
    D_kernel_bss_92D40[D_kernel_bss_92D00].c = c;
    intr = DIntr();
    D_kernel_bss_92D00 = (D_kernel_bss_92D00 + 1) % 512;
    if (intr) {
        EIntr();
    }
    return 0;
}
