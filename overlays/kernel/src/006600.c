/* KERNEL.XFF @ 0x006600 (196 B) - iosCreateThreadS
 * Evidence: allocates a 16-aligned stack with iosMallocAlign(ptn, size, 0x10); on failure iosJumpRecoverPoint(.rodata+0x878) and NULL; otherwise iosCreateThread(func, stack, size, prio, arg); a created thread gets flag bit 0 at +0x18, a failed one frees the stack. Second argument unused. UNCONFIRMED: names.
 */
struct IosThread {
    char pad0[0x18];
    unsigned int flags;
};
extern char D_kernel_rodata_0878[];
void *iosMallocAlign(void *ptn, int size, int align);
void iosFree(void *p);
void iosJumpRecoverPoint(const char *fmt, ...);
struct IosThread *iosCreateThread(void (*func)(void), void *stack, int size, int prio, int arg);
struct IosThread *iosCreateThreadS(void (*func)(void), int unused, void *ptn, int size, int prio, int arg) {
    void *stack;
    struct IosThread *th = 0;

    stack = iosMallocAlign(ptn, size, 0x10);
    if (stack == 0) {
        iosJumpRecoverPoint(D_kernel_rodata_0878);
    } else {
        th = iosCreateThread(func, stack, size, prio, arg);
        if (th != 0) {
            th->flags |= 1;
        } else {
            iosFree(stack);
        }
    }
    return th;
}
