/* KERNEL.XFF @ 0x01F698 (148 B) - Sg2CtrlEntryTickProc
 * Evidence: under DIntr/EIntr, finds the first of the 16 tick-table entries (.bss+0x7F540, 8 bytes each) still holding the default handler (static .text+0x1F690) and installs func there through Sg2CtrlEntryTickProcById; returns 0, or -1 when the table is full. UNCONFIRMED: names.
 */
struct TickProc {
    void (*func)(void);
    int count;
};
extern struct TickProc D_kernel_bss_7F540[16];
void func_01F690(void);
int DIntr(void);
int EIntr(void);
int Sg2CtrlEntryTickProcById(int id, void (*func)(void));

int Sg2CtrlEntryTickProc(void (*func)(void)) {
    int ret = -1;
    int intr = DIntr();
    int i;

    for (i = 0; i < 16; i++) {
        if (D_kernel_bss_7F540[i].func == func_01F690) {
            Sg2CtrlEntryTickProcById(i, func);
            ret = 0;
            break;
        }
    }
    if (intr) {
        EIntr();
    }
    return ret;
}
