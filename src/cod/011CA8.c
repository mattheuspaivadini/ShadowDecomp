/* asm/cod/011CA8.s -> sceSifExecNotifyHandler.
 * SCE sif notify dispatcher: walks a 16-byte handler table (the 32 fixed slots
 * at D_0014AC88, or the D_00133938/D_0013393C table) and calls each handler on
 * its own $gp, restoring the caller's $gp at the end.
 * MATCHED. */
struct NotifyHandler {
    void (*func)(void *, void *);   /* 0x00 */
    void *arg;                      /* 0x04 */
    int   gp;                       /* 0x08 the handler's $gp */
    int   pad0C;
};

extern struct NotifyHandler D_0014AC88[32];
extern struct NotifyHandler *D_00133938 __attribute__((section(".data")));
extern int D_0013393C __attribute__((section(".data")));

/* read $gp; old = $gp, $gp = new. As static inline functions (not macros) the
   call target lands in $a2 as in the image. (UNCONFIRMED: the SDK helpers' names.) */
static __inline__ int get_gp(void)
{
    int gp;
    __asm__ __volatile__ ("move %0, $gp" : "=r" (gp));
    return gp;
}

static __inline__ int set_gp(int gp)
{
    int old;
    __asm__ __volatile__ ("move %0, $gp
	move $gp, %1" : "=&r" (old) : "r" (gp) : "memory");
    return old;
}

void sceSifExecNotifyHandler(int intr, void *data) {
    struct NotifyHandler *tbl;
    struct NotifyHandler *h;
    int n;
    int i;
    int gp;

    if (intr) {
        tbl = D_0014AC88;
        n = 0x20;
    } else {
        tbl = D_00133938;
        n = D_0013393C;
    }
    gp = get_gp();
    for (i = 0; i < n; i++) {
        if (tbl[i].func) {
            set_gp(tbl[i].gp);
            tbl[i].func(data, tbl[i].arg);
        }
    }
    set_gp(gp);
}
