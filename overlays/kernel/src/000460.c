/* KERNEL.XFF @ 0x000460 (44 B) - iosCdStStart
 * Evidence: copies the pointer slot .bss+0x10 into .bss+0xC and stores
 * `(lsn + .bss+0x14) << 11` (`addu` then 64-bit `dsll 11`, i.e. sectors to
 * bytes) into the u64 at .bss+0x8050 (the stream position iosCdStSkip advances).
 * UNCONFIRMED: object names.
 */
extern unsigned long D_kernel_bss_8050;
extern void *D_kernel_bss_0010;
extern void *D_kernel_bss_000C;
extern int D_kernel_bss_0014;

void iosCdStStart(int lsn) {
    D_kernel_bss_000C = D_kernel_bss_0010;
    D_kernel_bss_8050 = (long)(lsn + D_kernel_bss_0014) << 11;
}
