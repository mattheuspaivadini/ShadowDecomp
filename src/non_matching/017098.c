/* STATUS (Session 28, 2026-10-18): NON_MATCHING. best score 5 [cc=29].
 * Residual = SignalSema(D_00133A60): the original keeps the load after the sceCdCbfunc_num = -1 store (lw lands in the jal slot); ours hoists it and leaves a nop. volatile D_00133A60 restores the order but a volatile load never enters a delay slot (score 28); -fno-schedule-insns{,2}, volatile on/off for sceCdCbfunc_num and permute_gen/types/stmts give no 0.
 * The original .s stays in the build (asm/cod/017098.s); this C
 * draft (Session 28) is kept for the record. */
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
