/* KERNEL.XFF @ 0x003758 (128 B) - iosMallocAlignNoCheck
 * Evidence: the static allocator at .text+0x1428 gets (ptn, size, align, caller pc) under the allocator semaphore (.bss+0x90B8), the result returned. The caller address is read from \$ra at entry (register variable bound to \$31; GAS move = daddu s4,ra,zero), not via __builtin_return_address (which reloads the saved slot).
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
void *func_001428(void *ptn, int size, int align, void *pc);

void *iosMallocAlignNoCheck(void *ptn, int size, int align) {
    register void *ra __asm__("$31");
    void *pc = ra;
    void *p;

    WaitSema(D_kernel_bss_90B8);
    p = func_001428(ptn, size, align, pc);
    SignalSema(D_kernel_bss_90B8);
    return p;
}
