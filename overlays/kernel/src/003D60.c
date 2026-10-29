/* KERNEL.XFF @ 0x003D60 (248 B) - iosMcInit
 * STATUS: NON-MATCHING 2/62 words (flags -G0 -fno-strict-aliasing -fno-gcse; -fno-cse-follow-jumps/-skip-blocks/-rerun-loop-opt make no difference).
 * Only residual: image emits `lui v1` (for the 92C0 element pointer s0) before `lui v0` (90C0 socket base s2) while keeping addiu s2 before addiu s0;
 * ours has the two lui register numbers swapped. Tried: sock/p assignment order swap (4 diffs), all-in-for-header init, `sock += 0x100` in the for
 * expression, `sock = sock + 0x100`, -fno-schedule-insns (6), -fno-regmove (7), -fno-strength-reduce (15).
 */
struct McPort {
    unsigned int sock;   /* 0x00 */
    int fd;              /* 0x04 */
    int proto;           /* 0x08 */
    int mode;            /* 0x0C */
    int unk10;           /* 0x10 */
    int pad[5];          /* 0x14..0x27 */
};
extern struct McPort D_kernel_bss_92C0[2];
extern char D_kernel_bss_90C0[];
extern char D_kernel_rodata_758[];

extern void iosLoaderResetEntry(void *func);
extern void func_00004588(void);
extern int sceMc2Init(int mode);
extern void LoaderSysPrintf(const char *fmt, ...);
extern int sceMc2CreateSocket(int *arg, void *buf);
extern int sceMc2Sync(int a, int b);
void iosMcInit(void)
{
    struct McPort *p;
    int i;
    unsigned int sock;

    for (i = 1; i >= 0; i--)
        D_kernel_bss_92C0[i].fd = -1;
    iosLoaderResetEntry(func_00004588);
    if (sceMc2Init(0))
        LoaderSysPrintf(D_kernel_rodata_758);
    sock = (unsigned int)D_kernel_bss_90C0;
    p = D_kernel_bss_92C0;
    for (i = 0; i < 2; i++, p++) {
        p->sock = sock;
        p->proto = 2;
        p->mode = (i == 0) ? 2 : 3;
        p->unk10 = 0;
        p->fd = sceMc2CreateSocket(&p->proto, (void *)sock);
        sceMc2Sync(0, 0);
        sock += 0x100;
    }
}
