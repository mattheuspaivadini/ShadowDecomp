/* STATUS (Session 22, 2026-10-17): NON_MATCHING. best score 3 [cc=29].
 * volatile cd-callback globals; residual = v0/v1 roles of the D_00133A54 test
 * The original .s stays in the build (asm/cod/016CE8.s); this C
 * draft (Session 22) is kept for the record. */
extern volatile int sceCdCbfunc_num __attribute__((section(".data")));
extern volatile int sceCdCbfunc_number __attribute__((section(".data")));
extern volatile int _sceCd_c_cb_sem __attribute__((section(".data")));
extern volatile int _sceCd_ncmd_semid __attribute__((section(".data")));
extern void *D_00133A54 __attribute__((section(".data")));
extern void *D_00150E00 __attribute__((section(".bss")));
extern volatile int D_00133A60 __attribute__((section(".data")));
void iSignalSema(int sema);

void _sceCd_cd_callback(int *result) {
    sceCdCbfunc_num = *result;
    sceCdCbfunc_number = sceCdCbfunc_num;
    if (sceCdCbfunc_num == 0xB) {
        sceCdCbfunc_num = 0;
        _sceCd_c_cb_sem = 0;
        return;
    }
    iSignalSema(_sceCd_ncmd_semid);
    if (D_00133A54 != 0 && D_00150E00 != 0)
        iSignalSema(D_00133A60);
    else
        _sceCd_c_cb_sem = 0;
    sceCdCbfunc_num = 0;
}
