/* KERNEL.XFF @ 0x01F730 (64 B) - Sg2CtrlEntryTickProcById
 * Evidence: slot id of the 8-byte tick table at .bss+0x7F540 is taken only while it still holds the default handler (static .text+0x1F690); stores func and clears the arg; returns id or -1. UNCONFIRMED: names.
 */
struct TickProc {
    void (*func)(void);
    int arg;
};
extern struct TickProc D_kernel_bss_7F540[16];
void func_01F690(void);

int Sg2CtrlEntryTickProcById(int id, void (*func)(void)) {
    if (D_kernel_bss_7F540[id].func != func_01F690) {
        return -1;
    }
    D_kernel_bss_7F540[id].func = func;
    D_kernel_bss_7F540[id].arg = 0;
    return id;
}
