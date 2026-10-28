/* KERNEL.XFF @ 0x000748 (92 B) - iosCdInit
 * Evidence: sceCdInit(0), sceCdMmode(2) (DVD), then resets the stream state at .bss+0 (+1 = 1, +0/+2 = 0) and .bss+8 (+0/+2 = 0) and points both .bss+0xC and .bss+0x10 at .bss+0. The chained pointer assignment fixes the lui order. UNCONFIRMED: field names.
 */
struct CdState {
    unsigned char a;
    unsigned char b;
    unsigned char c;
};
extern struct CdState D_kernel_bss_0000;
extern struct CdState D_kernel_bss_0008;
extern struct CdState *D_kernel_bss_000C;
extern struct CdState *D_kernel_bss_0010;
int sceCdInit(int mode);
int sceCdMmode(int media);

void iosCdInit(void) {
    sceCdInit(0);
    sceCdMmode(2);
    D_kernel_bss_0000.a = 0;
    D_kernel_bss_0000.b = 1;
    D_kernel_bss_0000.c = 0;
    D_kernel_bss_0008.a = 0;
    D_kernel_bss_0008.c = 0;
    D_kernel_bss_0010 = D_kernel_bss_000C = &D_kernel_bss_0000;
}
