/* KERNEL.XFF @ 0x0139E0 (64 B) - InitDL
 * Evidence: calls the static at .text+0x13018, SignalSema(volatile .bss+0x1EAD0), then sets volatile .data+0x560 to 1. UNCONFIRMED: names.
 */
extern volatile int D_kernel_bss_1EAD0;
extern volatile int D_kernel_data_0560;
void func_013018(void);
int SignalSema(int sema);

void InitDL(void) {
    func_013018();
    SignalSema(D_kernel_bss_1EAD0);
    D_kernel_data_0560 = 1;
}
