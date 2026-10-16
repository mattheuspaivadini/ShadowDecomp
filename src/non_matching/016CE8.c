/* STATUS (Session 8, 2026-10-14): NON_MATCHING. best score 21 [cc=29].
 * R4 w25a_2: clean guess but not byte-exact
 * The original .s stays in the build (asm/cod/016CE8.s); this C
 * draft (Session 8) is kept for the record. */
extern int sceCdCbfunc_num[];
extern int sceCdCbfunc_number[];
extern int _sceCd_ncmd_semid[];
extern int _sceCd_c_cb_sem[];
extern int D_00133A54[];
extern int D_00133A60[];
extern int D_00150E00[];

void iSignalSema(int a0);

void _sceCd_cd_callback(int *a0) {
    sceCdCbfunc_num[0] = *a0;
    sceCdCbfunc_number[0] = sceCdCbfunc_num[0];
    if (sceCdCbfunc_num[0] == 0xB) {
        sceCdCbfunc_num[0] = 0;
        _sceCd_c_cb_sem[0] = 0;
        return;
    }
    iSignalSema(_sceCd_ncmd_semid[0]);
    if (D_00133A54[0] != 0 && D_00150E00[0] != 0)
        iSignalSema(D_00133A60[0]);
    else
        _sceCd_c_cb_sem[0] = 0;
    sceCdCbfunc_num[0] = 0;
}
