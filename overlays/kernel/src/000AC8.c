/* KERNEL.XFF @ 0x000AC8 (176 B) - iosInitIntrSystem
 * Evidence: T0_MODE (0x10000010) and T1_MODE (0x10000810) cleared, iosAddIntcHandler(9, static .text+0xEB8), T0/T1_COUNT cleared, T0_MODE = 0x280, T1_MODE = 0x80; a SemaParam {max 1, init 1} creates the semaphore (registered with LoaderSysEntryExternalSemaList) stored to .data+0xA8; .bss+0x90A8 = -1, .bss+0x90AC = 0. UNCONFIRMED: object names.
 */
struct SemaParam {
    int currentCount;
    int maxCount;
    int initCount;
    int numWaitThreads;
    unsigned int attr;
    unsigned int option;
};
extern int D_kernel_data_00A8;
extern int D_kernel_bss_90A8;
extern int D_kernel_bss_90AC;
void iosAddIntcHandler(int cause, void *handler);
void func_000EB8(void);
int CreateSema(struct SemaParam *p);
void LoaderSysEntryExternalSemaList(int sema);

void iosInitIntrSystem(void) {
    struct SemaParam p;
    int sema;

    *(volatile int *)0x10000010 = 0;
    *(volatile int *)0x10000810 = 0;
    iosAddIntcHandler(9, func_000EB8);
    *(volatile int *)0x10000000 = 0;
    *(volatile int *)0x10000800 = 0;
    *(volatile int *)0x10000010 = 0x280;
    *(volatile int *)0x10000810 = 0x80;
    p.initCount = 1;
    p.maxCount = 1;
    sema = CreateSema(&p);
    LoaderSysEntryExternalSemaList(sema);
    D_kernel_data_00A8 = sema;
    D_kernel_bss_90A8 = -1;
    D_kernel_bss_90AC = 0;
}
