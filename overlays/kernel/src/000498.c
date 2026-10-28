/* KERNEL.XFF @ 0x000498 (272 B) - iosCdStRead
 * Evidence: copies size bytes out of the CD stream buffer (.bss+0x40): while the 64-bit read position (.bss+0x8050) lies inside the buffered window [.bss+0x8040, .bss+0x8048) it memcpy's min(window end - pos, size) bytes and advances; otherwise the static at .text+0x30 refills from sector pos / 2048. UNCONFIRMED: names.
 */
extern char D_kernel_bss_0040[];
extern long D_kernel_bss_8040;
extern long D_kernel_bss_8048;
extern long D_kernel_bss_8050;
void *memcpy(void *d, const void *s, unsigned int n);
void func_000030(int sector);

void iosCdStRead(char *dst, int size) {
    int n;

    while (size > 0) {
        if (D_kernel_bss_8050 >= D_kernel_bss_8040 && D_kernel_bss_8050 < D_kernel_bss_8048) {
            n = D_kernel_bss_8048 - D_kernel_bss_8050;
            n = n < size ? n : size;
            memcpy(dst, D_kernel_bss_0040 + (int)(D_kernel_bss_8050 - D_kernel_bss_8040), n);
            size -= n;
            dst += n;
            D_kernel_bss_8050 += n;
        } else {
            func_000030(D_kernel_bss_8050 / 2048);
        }
    }
}
