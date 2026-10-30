/* KERNEL.XFF @ 0x00A5F8 (200 B) - readEModule
 * Evidence: strncmp(name, .rodata+0xBC0 = "cdrom0:", 7); when it matches, the
 * file name starts after the first ':' (strstr(.rodata+0xB90 = ":") + 1), the
 * CD is searched with sceCdSearchFile(&stat on the stack, name) and a failure
 * reports iosJumpRecoverPoint(.rodata+0xB98, name); the size is stat[1].
 * Otherwise the size comes from iosLoaderGetFileSizeName(name).  A negative
 * size returns 0; otherwise func_008B78(name, size, arg) is returned.
 * Lever: two source-level call sites (the compiler tail-merges them, giving
 * the a1-vs-v0 size copies) plus `register int ret asm("s2")` for the s2/s3
 * allocation swap.  UNCONFIRMED: prototypes, local names.
 * c_sources.txt: 00A5F8 = src/00A5F8.c -G0 -fno-strict-aliasing
 */
extern char D_kernel_rodata_B90[];
extern char D_kernel_rodata_B98[];
extern char D_kernel_rodata_BC0[];

extern int strncmp(const char *a, const char *b, int n);
extern char *strstr(const char *s, const char *sub);
extern int sceCdSearchFile(void *fp, char *name);
extern void iosJumpRecoverPoint(const char *fmt, ...);
extern int iosLoaderGetFileSizeName(char *name);
extern int func_008B78(char *name, int size, int arg);
int readEModule(char *name, int arg)
{
    register int ret asm("s2");
    int stat[12];
    ret = 0;
    if (strncmp(name, D_kernel_rodata_BC0, 7) == 0) {
        char *p = strstr(name, D_kernel_rodata_B90) + 1;
        if (sceCdSearchFile(stat, p) == 0)
            iosJumpRecoverPoint(D_kernel_rodata_B98, p);
        if (stat[1] >= 0)
            ret = func_008B78(name, stat[1], arg);
    } else {
        int size = iosLoaderGetFileSizeName(name);
        if (size >= 0)
            ret = func_008B78(name, size, arg);
    }
    return ret;
}
