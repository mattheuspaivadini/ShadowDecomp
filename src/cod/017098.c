/* asm/cod/017098.s -> func_00117098.
 * CD shutdown: signal/delete the command semaphores; an empty asm memory barrier after the callback-number store keeps sched2 from hoisting the D_00133A60 load (Session 32).
 * MATCHED. */
extern __attribute__((section(".data"))) int D_00133A54;
extern __attribute__((section(".data"))) int D_00133A60;
extern __attribute__((section(".data"))) int sceCdCbfunc_num;
extern __attribute__((section(".data"))) int _sceCd_ncmd_semid;
extern __attribute__((section(".data"))) int _sceCd_scmd_semid;
extern __attribute__((section(".data"))) int _sceCd_rcmd_semid;

int SignalSema(int semid);
int DeleteSema(int semid);
int DIntr(void);
int EIntr(void);
void sceSifRemoveCmdHandler(unsigned int cid);

void func_00117098(void) {
    int intr;
    if (D_00133A54 != 0) {
        sceCdCbfunc_num = -1;
        __asm__ __volatile__("" ::: "memory"); /* keeps the store ahead of the D_00133A60 address/load */
        SignalSema(D_00133A60);
    }
    DeleteSema(_sceCd_ncmd_semid);
    DeleteSema(_sceCd_scmd_semid);
    DeleteSema(_sceCd_rcmd_semid);
    DeleteSema(D_00133A60);
    intr = DIntr();
    sceSifRemoveCmdHandler(0x80000012u);
    if (intr != 0)
        EIntr();
}
