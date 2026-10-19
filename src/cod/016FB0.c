/* asm/cod/016FB0.s -> _sceCdInitSema.
 * a0 pinned before the last initCount store (register asm) and an asm memory barrier before the cb_sem store (Session 32).
 * MATCHED. */
/* Create the three CD command semaphores (n/s/rcmd, max 1, init 1) and the callback semaphore (init 0) when any id is still -1. */
struct SemaParam {
    int currentCount;   /* 0x00 */
    int maxCount;       /* 0x04 */
    int initCount;      /* 0x08 */
    int numWaitThreads; /* 0x0C */
    int attr;           /* 0x10 */
    int option;         /* 0x14 */
};

extern int _sceCd_ncmd_semid __attribute__((section(".data")));
extern int _sceCd_scmd_semid __attribute__((section(".data")));
extern int _sceCd_rcmd_semid __attribute__((section(".data")));
extern int _sceCd_c_cb_sem __attribute__((section(".data")));
extern int D_00133A60 __attribute__((section(".data")));
extern char D_001388A8[], D_001388B8[], D_001388C8[], D_001388D8[];

int CreateSema(struct SemaParam *param);

void _sceCdInitSema(void) {
    struct SemaParam sema;

    if (_sceCd_ncmd_semid == -1 || _sceCd_scmd_semid == -1 || _sceCd_rcmd_semid == -1) {
        sema.initCount = 1;
        sema.maxCount = 1;
        sema.option = (int)D_001388A8;
        _sceCd_ncmd_semid = CreateSema(&sema);
        sema.option = (int)D_001388B8;
        _sceCd_scmd_semid = CreateSema(&sema);
        sema.option = (int)D_001388C8;
        _sceCd_rcmd_semid = CreateSema(&sema);
        sema.option = (int)D_001388D8;
        {
            /* a0 set before the initCount store, which then fills the jal slot */
            register struct SemaParam *p asm("$4") = &sema;
            sema.initCount = 0;
            D_00133A60 = CreateSema(p);
        }
        __asm__ __volatile__("" ::: "memory"); /* keeps the cb_sem address in v0 */
        _sceCd_c_cb_sem = 0;
    }
}
