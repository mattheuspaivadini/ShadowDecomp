/* KERNEL.XFF @ 0x004220 (248 B) - iosMcReadFile
 * Evidence: port record = .bss+0x92C0 + port*0x28 (`sll/addu/sll 3` = *0x28),
 * fd at +0x4 (`lw a0,-0x6D3C(...)`); a non-zero flag prints
 * .rodata+0x670 through LoaderSysPrintf before the call; the five remaining
 * arguments go to sceMc2ReadFile(fd, buf, size, a4, a5).  A negative result
 * takes `code = ret & 0xFFFF` (`andi`) and scans the 22-entry 0xC-stride table
 * at .data+0x158 for `code`, default value 8.
 * LEVERS: (1) `unsigned int i` gives the shipped `sltiu $v0,$a3,0xB`;
 * (2) the test is written `code == D[i].code` (the `beq` encodes $a2 first);
 * (3) two separate subscripts (`D[i].code` in the test, `D[i].value` in the
 * found path) are what make loop.c strength-reduce two cursors - a pointer that
 * advances by 0xC and a byte offset used only by the found path (`addu v0,t0,a1`)
 * - which is the shape every single-subscript draft missed;
 * (4) `goto out` + one `return val` reproduces the shared tail.
 * UNCONFIRMED: record/table names and the meaning of the 8 default.
 */
extern char D_kernel_rodata_670[];
extern int LoaderSysPrintf(const char *fmt, ...);
extern int sceMc2ReadFile(int fd, void *buf, int size, int a3, int a4);

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

int iosMcReadFile(int port, int flag, void *buf, int size, int a4, int a5) {
    int ret;
    int code;
    unsigned int i;
    int val;

    if (flag)
        LoaderSysPrintf(D_kernel_rodata_670);
    ret = sceMc2ReadFile(D_kernel_bss_92C0[port].fd, buf, size, a4, a5);
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
