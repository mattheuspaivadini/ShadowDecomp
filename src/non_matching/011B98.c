/* STATUS (10, 2026-10-16): NON_MATCHING. best score 5 [cc=29].
 * 
 * The original .s stays in the build (asm/cod/011B98.s); this C
 * draft (10) is kept for the record. */
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
    register void *gp_reg asm("gp");

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
    table[idx].gp = gp_reg;
    if (intr) {
        EIntr();
    }
    return 0;
}
