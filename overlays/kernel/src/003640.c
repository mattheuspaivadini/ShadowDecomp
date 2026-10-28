/* KERNEL.XFF @ 0x003640 (280 B) - iosMallocAlign
 * Evidence: under the allocator semaphore (.bss+0x90B8) the static allocator at .text+0x1428 gets (ptn, size, align, caller pc from $ra); on failure it prints .rodata+0x188 (ptn, size, pc), dumps the partition with the static at .text+0x3CF0 (ptn, 1) and prints .rodata+0x1B8 with .data+0x148/.data+0xB4; after SignalSema a failure prints .rodata+0x1E8 with the out-of-memory hook (.data+0xB8), calls it when set, and ends in iosJumpRecoverPoint(.rodata+0x1F8, ptn, size, pc). UNCONFIRMED: names.
 */
extern int D_kernel_bss_90B8;
extern char D_kernel_data_0148[];
extern int D_kernel_data_00B4;
extern void (*D_kernel_data_00B8)(void);
extern char D_kernel_rodata_0188[];
extern char D_kernel_rodata_01B8[];
extern char D_kernel_rodata_01E8[];
extern char D_kernel_rodata_01F8[];
int WaitSema(int sema);
int SignalSema(int sema);
int LoaderSysPrintf(const char *fmt, ...);
void iosJumpRecoverPoint(const char *fmt, ...);
void *func_001428(void *ptn, int size, int align, void *pc);
void func_003CF0(void *ptn, int mode);

void *iosMallocAlign(void *ptn, int size, int align) {
    register void *ra __asm__("$31");
    void *pc = ra;
    void *p;

    WaitSema(D_kernel_bss_90B8);
    p = func_001428(ptn, size, align, pc);
    if (p == 0) {
        LoaderSysPrintf(D_kernel_rodata_0188, ptn, size, pc);
        func_003CF0(ptn, 1);
        LoaderSysPrintf(D_kernel_rodata_01B8, D_kernel_data_0148, D_kernel_data_00B4);
    }
    SignalSema(D_kernel_bss_90B8);
    if (p == 0) {
        LoaderSysPrintf(D_kernel_rodata_01E8, D_kernel_data_00B8);
        if (D_kernel_data_00B8 != 0) {
            D_kernel_data_00B8();
        }
        iosJumpRecoverPoint(D_kernel_rodata_01F8, ptn, size, pc);
    }
    return p;
}
