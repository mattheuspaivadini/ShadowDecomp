/* KERNEL.XFF @ 0x0008D8 (144 B) - func_0008D8 (static, no symbol in the shipped .symtab)
 * Evidence: thread loop: iosRecvMsg(.bss+0x8070, 0, 0) per tick; when the countdown at .data+8 drops below 0, sceCdReadClock into a local and, on success with stat 0, the 8-byte clock goes to .bss+0x9098; countdown reset to 1000000. UNCONFIRMED: names; Ghidra FUN_002008d8.
 */
union CdClock {
    struct {
        unsigned char stat;
        unsigned char second;
        unsigned char minute;
        unsigned char hour;
        unsigned char pad;
        unsigned char day;
        unsigned char month;
        unsigned char year;
    } c;
    unsigned long v;
};
extern char D_kernel_bss_08070[];
extern int D_kernel_data_0008;
extern unsigned long D_kernel_bss_09098;
int iosRecvMsg(void *box, void *msg, int mode);
int sceCdReadClock(union CdClock *clk);

void func_0008D8(void) {
    union CdClock clk;

    for (;;) {
        iosRecvMsg(D_kernel_bss_08070, 0, 0);
        if (--D_kernel_data_0008 >= 0) {
            continue;
        }
        if (sceCdReadClock(&clk) == 1 && clk.c.stat == 0) {
            D_kernel_bss_09098 = clk.v;
        }
        D_kernel_data_0008 = 1000000;
    }
}
