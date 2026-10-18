/* asm/cod/00A7D8.s -> scePowerOffHandler.
 * power-off handler install; callback struct pointer kept across calls, $gp saved via a register asm("$28") local (Session 22)
 * MATCHED. */
struct PwrCb { void *func; void *addr; };
void func_0010A798(int a0);
int sceFsInit(void);
void func_0010A7C8(void);
int DIntr(void);
int EIntr(void);

extern int D_00132314 __attribute__((section(".data")));
extern struct PwrCb D_00147140 __attribute__((section(".bss")));
extern void *D_00147180 __attribute__((section(".bss")));

void *scePowerOffHandler(void *func, void *addr) {
    struct PwrCb *p = &D_00147140;
    void *old;
    int g;

    func_0010A798(0x1B);
    if (D_00132314 == 0)
        sceFsInit();
    g = DIntr();
    old = p->func;
    p->addr = addr;
    p->func = func;
    {
        register void *gp asm("$28");
        D_00147180 = gp;
    }
    if (g)
        EIntr();
    func_0010A7C8();
    return old;
}
