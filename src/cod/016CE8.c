/* asm/cod/016CE8.s -> _sceCd_cd_callback.
 * Register the callback condition in v0 to match the original test sequence.
 * MATCHED. */
extern volatile int sceCdCbfunc_num __attribute__((section(".data")));
extern volatile int sceCdCbfunc_number __attribute__((section(".data")));
extern volatile int _sceCd_c_cb_sem __attribute__((section(".data")));
extern volatile int _sceCd_ncmd_semid __attribute__((section(".data")));
extern void *D_00133A54 __attribute__((section(".data")));
extern void *D_00150E00 __attribute__((section(".bss")));
extern volatile int D_00133A60 __attribute__((section(".data")));
void iSignalSema(int sema);

void _sceCd_cd_callback(int *result) {
    register void *cond asm ("$2");
    sceCdCbfunc_num = *result;
    sceCdCbfunc_number = sceCdCbfunc_num;
    if (sceCdCbfunc_num == 0xB) {
        sceCdCbfunc_num = 0;
        _sceCd_c_cb_sem = 0;
        return;
    }
    iSignalSema(_sceCd_ncmd_semid);
    cond = D_00133A54;
    if (cond && D_00150E00)
        iSignalSema(D_00133A60);
    else
        _sceCd_c_cb_sem = 0;
    sceCdCbfunc_num = 0;
}
