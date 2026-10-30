/* KERNEL.XFF @ 0x02f438 (224 B) - Sg2ExPcmOutputOpen
 * Evidence: returns -1 when the PCM-out record's buffer (+0xC at
 * .bss+0x9BE20) is already allocated; `malloc(samples/2*4)` (`sra` halving
 * shows a signed /2) is stored before the NULL test, so the assignment sits in
 * the `if` condition; returns -2 on allocation failure.  Under DIntr/EIntr it
 * fills +0x14, +0x1A8, +0x1A4, +8, +0x1B0, +0x10 with (arg2, arg2, arg0, arg1,
 * 0, arg2), zeroes +0x18 around Sg2ExPcmOutputBufferClear, zeroes +0x1AC
 * around Sg2ExPcmOutputAutoFilterInit(0/1) and sets the state at +0 to 1.
 * The store order in the source must be f1A8, f1A4, f8, f1B0, f10, f14 and the
 * redundant f18 store on both sides of the buffer-clear call is real.
 * UNCONFIRMED: record field names, argument meanings.
 * Flags: -g0 (delayed-branch scheduler) required for the epilogue shape.
 */
struct PcmOutput {
    int f0;
    int f4;
    int f8;
    void *buf;
    int f10;
    int f14;
    int f18;
    char pad1C[0x1A4 - 0x1C];
    int f1A4;
    int f1A8;
    int f1AC;
    int f1B0;
};
extern struct PcmOutput D_kernel_bss_9BE20;
void *malloc(unsigned int n);
int DIntr(void);
int EIntr(void);
void func_02F578(void);
void func_02F6E0(int on);

int Sg2ExPcmOutputOpen(int a0, int a1, int a2) {
    int intr;

    if (D_kernel_bss_9BE20.buf != 0) {
        return -1;
    }
    if ((D_kernel_bss_9BE20.buf = malloc(a2 / 2 * 4)) == 0) {
        return -2;
    }
    intr = DIntr();
    D_kernel_bss_9BE20.f1A8 = a2;
    D_kernel_bss_9BE20.f1A4 = a0;
    D_kernel_bss_9BE20.f8 = a1;
    D_kernel_bss_9BE20.f1B0 = 0;
    D_kernel_bss_9BE20.f10 = a2;
    D_kernel_bss_9BE20.f14 = a2;
    D_kernel_bss_9BE20.f18 = 0;
    func_02F578();
    D_kernel_bss_9BE20.f18 = 0;
    D_kernel_bss_9BE20.f1AC = 0;
    func_02F6E0(0);
    func_02F6E0(1);
    D_kernel_bss_9BE20.f0 = 1;
    if (intr) {
        EIntr();
    }
    return 0;
}
