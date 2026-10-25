/* KERNEL.XFF @ 0x004410 (72 B) - iosMcFormat
 * Evidence: optional LoaderSysPrintf(.rodata+0x670) when the second argument is set, then sibling sceMc2Format(word 0 of the 40-byte per-port record at .bss+0x92C4). UNCONFIRMED: record layout.
 */
struct McPort {
    int fd;
    char pad[36];
};
extern struct McPort D_kernel_bss_92C4[];
extern char D_kernel_rodata_0670[];
int LoaderSysPrintf(const char *fmt, ...);
int sceMc2Format(int fd);

int iosMcFormat(int port, int verbose) {
    if (verbose) {
        LoaderSysPrintf(D_kernel_rodata_0670);
    }
    return sceMc2Format(D_kernel_bss_92C4[port].fd);
}
