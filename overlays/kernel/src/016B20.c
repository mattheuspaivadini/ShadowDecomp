/* KERNEL.XFF @ 0x016B20 (204 B) - bootGPThread
 * Evidence: InitDL(0x7C80, 0x20); start time (.bss+0x1F0D0, volatile u64: lui/addiu+0 store) = iosGetTCount(); GS CSR (0x12001000) |= 2; sceGsPutIMR(sceGsGetIMR() & ~0x200); iosAddIntcHandler(0, static .text+0x16E58); iosSetScreenEnv(); priority to .data+0x638; GP thread = iosCreateThread(static .text+0x16F40, stack .bss+0x1F0E0, 0x8000, 0x2A, 0) stored at .bss+0x1F0D8 and started; static .text+0x16738(1); sibling iosSyncV(0). UNCONFIRMED: names, InitDL arity.
 */
extern volatile unsigned long D_kernel_bss_1F0D0;
extern int D_kernel_bss_1F0D8;
extern char D_kernel_bss_1F0E0[];
extern int D_kernel_data_0638;
void InitDL(int size, int num);
unsigned long iosGetTCount(void);
unsigned long sceGsGetIMR(void);
unsigned long sceGsPutIMR(unsigned long imr);
void iosAddIntcHandler(int cause, void *handler);
void iosSetScreenEnv(void);
int iosCreateThread(void (*func)(void), void *stack, int size, int prio, int arg);
void iosStartThread(int thread, int arg);
int iosSyncV(int n);
static void func_016738(int a);
static void func_016E58(void);
static void func_016F40(void);

void bootGPThread(int prio) {
    InitDL(0x7C80, 0x20);
    D_kernel_bss_1F0D0 = iosGetTCount();
    *(volatile unsigned long *)0x12001000 |= 2;
    sceGsPutIMR(sceGsGetIMR() & ~0x200);
    iosAddIntcHandler(0, func_016E58);
    iosSetScreenEnv();
    D_kernel_data_0638 = prio;
    D_kernel_bss_1F0D8 = iosCreateThread(func_016F40, D_kernel_bss_1F0E0, 0x8000, 0x2A, 0);
    iosStartThread(D_kernel_bss_1F0D8, 0);
    func_016738(1);
    iosSyncV(0);
}
