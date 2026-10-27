/* KERNEL.XFF @ 0x01B528 (156 B) - bootSchedulerThread
 * Evidence: iosPadInit(); .data+0x7E0 = 0; iosCreateIVArbitrationSema(); thread (static .text+0x1B708, stack .bss+0x791D0, 0x1000, prio 0x28) stored at .bss+0x791C4 and started; iosAddIntcHandler(2, static .text+0x1B7E8); thread (static .text+0x1B148, stack .bss+0x7A210, 0x2000, prio 0x2D) stored at .bss+0x7A208 and started (sibling call). UNCONFIRMED: names.
 */
extern int D_kernel_data_07E0;
extern int D_kernel_bss_791C4;
extern char D_kernel_bss_791D0[];
extern int D_kernel_bss_7A208;
extern char D_kernel_bss_7A210[];
void iosPadInit(void);
void iosCreateIVArbitrationSema(void);
int iosCreateThread(void (*func)(void), void *stack, int size, int prio, int arg);
void iosStartThread(int thread, int arg);
void iosAddIntcHandler(int cause, void *handler);
static void func_01B148(void);
static void func_01B708(void);
static void func_01B7E8(void);

void bootSchedulerThread(void) {
    iosPadInit();
    D_kernel_data_07E0 = 0;
    iosCreateIVArbitrationSema();
    D_kernel_bss_791C4 = iosCreateThread(func_01B708, D_kernel_bss_791D0, 0x1000, 0x28, 0);
    iosStartThread(D_kernel_bss_791C4, 0);
    iosAddIntcHandler(2, func_01B7E8);
    D_kernel_bss_7A208 = iosCreateThread(func_01B148, D_kernel_bss_7A210, 0x2000, 0x2D, 0);
    iosStartThread(D_kernel_bss_7A208, 0);
}
