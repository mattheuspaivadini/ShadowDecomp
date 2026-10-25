/* KERNEL.XFF @ 0x004458 (72 B) - iosMcUnformat
 * Evidence: optional LoaderSysPrintf(.rodata+0x670) when the second argument is set, then sibling sceMc2Unformat(word 0 of the 40-byte per-port record at .bss+0x92C4). UNCONFIRMED: record layout.
 */
struct McPort {
    int fd;
    char pad[36];
};
extern struct McPort D_kernel_bss_92C4[];
extern char D_kernel_rodata_0670[];
int LoaderSysPrintf(const char *fmt, ...);
int sceMc2Unformat(int fd);

int iosMcUnformat(int port, int verbose) {
    if (verbose) {
        LoaderSysPrintf(D_kernel_rodata_0670);
    }
    return sceMc2Unformat(D_kernel_bss_92C4[port].fd);
}
