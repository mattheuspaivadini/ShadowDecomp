/* KERNEL.XFF @ 0x004318 (248 B) - iosMcWriteFile
 * Evidence: byte-identical to iosMcReadFile (0x004220) apart from the callee
 * (sceMc2WriteFile) and the symbol, so the same source shape applies: port
 * record .bss+0x92C0 + port*0x28 with fd at +0x4, optional LoaderSysPrintf of
 * .rodata+0x670, the call's five arguments, and the negative-result path that
 * masks the error code and scans the 22-entry 0xC-stride table at .data+0x158
 * (default 8).  See 004220.c for the levers (unsigned index, `code == D[i].code`,
 * two subscripts for the two strength-reduced cursors, `goto` to the shared tail).
 * UNCONFIRMED: record/table names and the meaning of the 8 default.
 */
extern char D_kernel_rodata_670[];
extern int LoaderSysPrintf(const char *fmt, ...);
extern int sceMc2WriteFile(int fd, void *buf, int size, int a3, int a4);

struct McPort {
    int unk00;
    int fd;
    char pad[0x20];
};
extern struct McPort D_kernel_bss_92C0[];

struct McEntry {
    int code;
    int value;
    int msg;
};
extern struct McEntry D_kernel_data_158[];

int iosMcWriteFile(int port, int flag, void *buf, int size, int a4, int a5) {
    int ret;
    int code;
    unsigned int i;
    int val;

    if (flag)
        LoaderSysPrintf(D_kernel_rodata_670);
    ret = sceMc2WriteFile(D_kernel_bss_92C0[port].fd, buf, size, a4, a5);
    if (ret >= 0)
        return 0;
    code = ret & 0xFFFF;
    val = 8;
    i = 0;
    while (i < 22) {
        if (code == D_kernel_data_158[i].code) {
            val = D_kernel_data_158[i].value;
            goto out;
        }
        i++;
    }
out:
    return val;
}
