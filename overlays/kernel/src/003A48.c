/* KERNEL.XFF @ 0x003A48 (112 B) - iosCreatePartition
 * Evidence: the static at .text+0x2A80 gets (parent, size, caller pc) under the allocator semaphore (.bss+0x90B8), the result returned. The caller address is read from \$ra at entry (register variable bound to \$31; GAS move = daddu s4,ra,zero), not via __builtin_return_address (which reloads the saved slot).
 */
extern int D_kernel_bss_90B8;
int WaitSema(int sema);
int SignalSema(int sema);
void *func_002A80(void *parent, int size, void *pc);

void *iosCreatePartition(void *parent, int size) {
    register void *ra __asm__("$31");
    void *pc = ra;
    void *r;

    WaitSema(D_kernel_bss_90B8);
    r = func_002A80(parent, size, pc);
    SignalSema(D_kernel_bss_90B8);
    return r;
}
