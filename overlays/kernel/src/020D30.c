/* KERNEL.XFF @ 0x020D30 (48 B) - Sg2ExStAdpcmSetOutputMode
 * Evidence: stores mode into the volatile .bss+0x7F5F8 and, when the first argument is set, tail-calls the static at .text+0x20A20. UNCONFIRMED: names.
 */
extern volatile int D_kernel_bss_7F5F8;
void func_020A20(void);

void Sg2ExStAdpcmSetOutputMode(int apply, int mode) {
    D_kernel_bss_7F5F8 = mode;
    if (apply) {
        func_020A20();
    }
}
