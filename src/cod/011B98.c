/* asm/cod/011B98.s -> sceSifAddRebootNotifyHandler.
 * SCE sifcmd reboot notify; $gp captured with asm volatile move (Session 19)
 * MATCHED. */
typedef struct {
    void *func;
    void *arg;
    void *gp;
    int pad;
} SifRebootNotifyHandler;

extern int DIntr(void);
extern int EIntr(void);

extern SifRebootNotifyHandler *D_00133938[];
extern unsigned int D_0013393C[];
extern SifRebootNotifyHandler D_0014AC88[];

int sceSifAddRebootNotifyHandler(unsigned int idx, void *func, void *arg) {
    SifRebootNotifyHandler *table;
    unsigned int max;
    int intr;
    void *gp;

    if ((int)idx < 0) {
        idx &= 0x7fffffff;
        table = D_0014AC88;
        max = 0x20;
    } else {
        table = D_00133938[0];
        max = D_0013393C[0];
    }
    if (idx >= max) {
        return 0x80000069;
    }
    intr = DIntr();
    table[idx].func = func;
    table[idx].arg = arg;
    __asm__ volatile ("move %0, $gp" : "=r" (gp));
    table[idx].gp = gp;
    if (intr) {
        EIntr();
    }
    return 0;
}
