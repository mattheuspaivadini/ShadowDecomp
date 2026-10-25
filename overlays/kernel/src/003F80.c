/* KERNEL.XFF @ 0x003F80 (168 B) - iosMcChDir
 * Evidence: sceMc2Chdir(fd, path, NULL); the libmc2 result (low 16 bits) is translated through the 22-entry {code, result, ?} table at .data+0x158 (default 8, inlined do-while search); optional LoaderSysPrintf(.rodata+0x670) when verbose; fd from the 40-byte per-port record at .bss+0x92C4. UNCONFIRMED: table/record names.
 */
struct McPort {
    int fd;
    char pad[36];
};
struct McErr {
    int code;
    int result;
    int unk8;
};
extern struct McPort D_kernel_bss_92C4[];
extern struct McErr D_kernel_data_0158[22];
extern char D_kernel_rodata_0670[];
int LoaderSysPrintf(const char *fmt, ...);

static __inline__ int mcConvErr(int code) {
    int ret = 8;
    struct McErr *e = D_kernel_data_0158;
    unsigned int i;

    code &= 0xFFFF;
    i = 0;
    do {
        if (code == e->code) {
            ret = e->result;
            break;
        }
        i++;
        e++;
    } while (i < 22);
    return ret;
}
int sceMc2Chdir(int fd, const char *path, char *cur);

int iosMcChDir(int port, int verbose, const char *path) {
    if (verbose) {
        LoaderSysPrintf(D_kernel_rodata_0670);
    }
    return mcConvErr(sceMc2Chdir(D_kernel_bss_92C4[port].fd, path, 0));
}
