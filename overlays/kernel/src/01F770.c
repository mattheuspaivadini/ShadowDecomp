/* KERNEL.XFF @ 0x01F770 (184 B) - Sg2CtrlRemoveTickProc
 * Evidence: under DIntr/EIntr, finds the tick-table entry whose handler is func, clears its count and restores the default handler (static .text+0x1F690); returns 0, or -1 when absent (GCC peels the i = 0 test). UNCONFIRMED: names.
 */
struct TickProc {
    void (*func)(void);
    int count;
};
extern struct TickProc D_kernel_bss_7F540[16];
void func_01F690(void);
int DIntr(void);
int EIntr(void);

int Sg2CtrlRemoveTickProc(void (*func)(void)) {
    int ret = -1;
    int intr = DIntr();
    int i;

    for (i = 0; i < 16; i++) {
        if (D_kernel_bss_7F540[i].func == func) {
            D_kernel_bss_7F540[i].count = 0;
            D_kernel_bss_7F540[i].func = func_01F690;
            ret = 0;
            break;
        }
    }
    if (intr) {
        EIntr();
    }
    return ret;
}
